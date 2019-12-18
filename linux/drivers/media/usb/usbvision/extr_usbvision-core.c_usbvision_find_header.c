#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int frame_num; scalar_t__ data_format; int format_param; int frame_width; int frame_height; int /*<<< orphan*/  frame_latency; int /*<<< orphan*/  frame_phase; int /*<<< orphan*/  header_length; int /*<<< orphan*/  magic_1; int /*<<< orphan*/  magic_2; } ;
struct TYPE_3__ {int depth; } ;
struct usbvision_frame {int frmwidth; int frmheight; int v4l2_linesize; scalar_t__ curline; int /*<<< orphan*/  scanstate; TYPE_2__ isoc_header; TYPE_1__ v4l2_format; } ;
struct usb_usbvision {int last_isoc_frame_num; int stretch_width; int stretch_height; int /*<<< orphan*/  header_count; scalar_t__ request_intra; struct usbvision_frame* cur_frame; } ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_HEADER ; 
 scalar_t__ ISOC_MODE_COMPRESS ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ USBVISION_HEADER_LENGTH ; 
 int parse_state_continue ; 
 int parse_state_end_parse ; 
 int parse_state_next_frame ; 
 int /*<<< orphan*/  scan_state_lines ; 
 scalar_t__ scratch_get_header (struct usb_usbvision*,TYPE_2__*) ; 
 int /*<<< orphan*/  scratch_reset (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_request_intra (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_unrequest_intra (struct usb_usbvision*) ; 

__attribute__((used)) static enum parse_state usbvision_find_header(struct usb_usbvision *usbvision)
{
	struct usbvision_frame *frame;
	int found_header = 0;

	frame = usbvision->cur_frame;

	while (scratch_get_header(usbvision, &frame->isoc_header) == USBVISION_HEADER_LENGTH) {
		/* found header in scratch */
		PDEBUG(DBG_HEADER, "found header: 0x%02x%02x %d %d %d %d %#x 0x%02x %u %u",
				frame->isoc_header.magic_2,
				frame->isoc_header.magic_1,
				frame->isoc_header.header_length,
				frame->isoc_header.frame_num,
				frame->isoc_header.frame_phase,
				frame->isoc_header.frame_latency,
				frame->isoc_header.data_format,
				frame->isoc_header.format_param,
				frame->isoc_header.frame_width,
				frame->isoc_header.frame_height);

		if (usbvision->request_intra) {
			if (frame->isoc_header.format_param & 0x80) {
				found_header = 1;
				usbvision->last_isoc_frame_num = -1; /* do not check for lost frames this time */
				usbvision_unrequest_intra(usbvision);
				break;
			}
		} else {
			found_header = 1;
			break;
		}
	}

	if (found_header) {
		frame->frmwidth = frame->isoc_header.frame_width * usbvision->stretch_width;
		frame->frmheight = frame->isoc_header.frame_height * usbvision->stretch_height;
		frame->v4l2_linesize = (frame->frmwidth * frame->v4l2_format.depth) >> 3;
	} else { /* no header found */
		PDEBUG(DBG_HEADER, "skipping scratch data, no header");
		scratch_reset(usbvision);
		return parse_state_end_parse;
	}

	/* found header */
	if (frame->isoc_header.data_format == ISOC_MODE_COMPRESS) {
		/* check isoc_header.frame_num for lost frames */
		if (usbvision->last_isoc_frame_num >= 0) {
			if (((usbvision->last_isoc_frame_num + 1) % 32) != frame->isoc_header.frame_num) {
				/* unexpected frame drop: need to request new intra frame */
				PDEBUG(DBG_HEADER, "Lost frame before %d on USB", frame->isoc_header.frame_num);
				usbvision_request_intra(usbvision);
				return parse_state_next_frame;
			}
		}
		usbvision->last_isoc_frame_num = frame->isoc_header.frame_num;
	}
	usbvision->header_count++;
	frame->scanstate = scan_state_lines;
	frame->curline = 0;

	return parse_state_continue;
}