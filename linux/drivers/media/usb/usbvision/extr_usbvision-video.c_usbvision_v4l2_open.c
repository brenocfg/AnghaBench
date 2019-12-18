#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_usbvision {int initialized; int /*<<< orphan*/  v4l2_lock; scalar_t__ user; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_IO ; 
 int EBUSY ; 
 int ERESTARTSYS ; 
 scalar_t__ ISOC_MODE_COMPRESS ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isoc_mode ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbvision_begin_streaming (struct usb_usbvision*) ; 
 int usbvision_decompress_alloc (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_decompress_free (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_empty_framequeues (struct usb_usbvision*) ; 
 int usbvision_init_isoc (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_muxsel (struct usb_usbvision*,int /*<<< orphan*/ ) ; 
 int usbvision_scratch_alloc (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_scratch_free (struct usb_usbvision*) ; 
 int usbvision_setup (struct usb_usbvision*,scalar_t__) ; 
 int v4l2_fh_open (struct file*) ; 
 struct usb_usbvision* video_drvdata (struct file*) ; 

__attribute__((used)) static int usbvision_v4l2_open(struct file *file)
{
	struct usb_usbvision *usbvision = video_drvdata(file);
	int err_code = 0;

	PDEBUG(DBG_IO, "open");

	if (mutex_lock_interruptible(&usbvision->v4l2_lock))
		return -ERESTARTSYS;

	if (usbvision->user) {
		err_code = -EBUSY;
	} else {
		err_code = v4l2_fh_open(file);
		if (err_code)
			goto unlock;

		/* Allocate memory for the scratch ring buffer */
		err_code = usbvision_scratch_alloc(usbvision);
		if (isoc_mode == ISOC_MODE_COMPRESS) {
			/* Allocate intermediate decompression buffers
			   only if needed */
			err_code = usbvision_decompress_alloc(usbvision);
		}
		if (err_code) {
			/* Deallocate all buffers if trouble */
			usbvision_scratch_free(usbvision);
			usbvision_decompress_free(usbvision);
		}
	}

	/* If so far no errors then we shall start the camera */
	if (!err_code) {
		/* Send init sequence only once, it's large! */
		if (!usbvision->initialized) {
			int setup_ok = 0;
			setup_ok = usbvision_setup(usbvision, isoc_mode);
			if (setup_ok)
				usbvision->initialized = 1;
			else
				err_code = -EBUSY;
		}

		if (!err_code) {
			usbvision_begin_streaming(usbvision);
			err_code = usbvision_init_isoc(usbvision);
			/* device must be initialized before isoc transfer */
			usbvision_muxsel(usbvision, 0);

			/* prepare queues */
			usbvision_empty_framequeues(usbvision);
			usbvision->user++;
		}
	}

unlock:
	mutex_unlock(&usbvision->v4l2_lock);

	PDEBUG(DBG_IO, "success");
	return err_code;
}