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
struct file {int dummy; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXUSB_OPEN_ANALOG ; 
 int /*<<< orphan*/  OPS ; 
 int cxusb_medion_get (struct dvb_usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxusb_medion_put (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 int v4l2_fh_open (struct file*) ; 
 struct dvb_usb_device* video_drvdata (struct file*) ; 

__attribute__((used)) static int cxusb_videoradio_open(struct file *f)
{
	struct dvb_usb_device *dvbdev = video_drvdata(f);
	int ret;

	/*
	 * no locking needed since this call only modifies analog
	 * state if there are no other analog handles currenly
	 * opened so ops done via them cannot create a conflict
	 */
	ret = cxusb_medion_get(dvbdev, CXUSB_OPEN_ANALOG);
	if (ret != 0)
		return ret;

	ret = v4l2_fh_open(f);
	if (ret != 0)
		goto ret_release;

	cxusb_vprintk(dvbdev, OPS, "got open\n");

	return 0;

ret_release:
	cxusb_medion_put(dvbdev);

	return ret;
}