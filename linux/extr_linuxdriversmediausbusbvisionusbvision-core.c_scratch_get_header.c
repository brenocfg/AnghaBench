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
struct usbvision_frame_header {scalar_t__ magic_1; scalar_t__ magic_2; int header_length; int frame_width_hi; int frame_height_hi; scalar_t__ frame_height_lo; scalar_t__ frame_height; scalar_t__ frame_width_lo; scalar_t__ frame_width; } ;
struct usb_usbvision {size_t scratch_headermarker_read_ptr; scalar_t__ scratch_headermarker_write_ptr; int /*<<< orphan*/ * scratch_headermarker; int /*<<< orphan*/  scratch_read_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SCRATCH ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,size_t) ; 
 int USBVISION_HEADER_LENGTH ; 
 scalar_t__ USBVISION_MAGIC_1 ; 
 scalar_t__ USBVISION_MAGIC_2 ; 
 int USBVISION_NUM_HEADERMARKER ; 
 int /*<<< orphan*/  scratch_get (struct usb_usbvision*,unsigned char*,int) ; 

__attribute__((used)) static int scratch_get_header(struct usb_usbvision *usbvision,
			      struct usbvision_frame_header *header)
{
	int err_code = 0;

	PDEBUG(DBG_SCRATCH, "from read_ptr=%d", usbvision->scratch_headermarker_read_ptr);

	while (usbvision->scratch_headermarker_write_ptr -
		usbvision->scratch_headermarker_read_ptr != 0) {
		usbvision->scratch_read_ptr =
			usbvision->scratch_headermarker[usbvision->scratch_headermarker_read_ptr];
		usbvision->scratch_headermarker_read_ptr += 1;
		usbvision->scratch_headermarker_read_ptr %= USBVISION_NUM_HEADERMARKER;
		scratch_get(usbvision, (unsigned char *)header, USBVISION_HEADER_LENGTH);
		if ((header->magic_1 == USBVISION_MAGIC_1)
			 && (header->magic_2 == USBVISION_MAGIC_2)
			 && (header->header_length == USBVISION_HEADER_LENGTH)) {
			err_code = USBVISION_HEADER_LENGTH;
			header->frame_width  = header->frame_width_lo  + (header->frame_width_hi << 8);
			header->frame_height = header->frame_height_lo + (header->frame_height_hi << 8);
			break;
		}
	}

	return err_code;
}