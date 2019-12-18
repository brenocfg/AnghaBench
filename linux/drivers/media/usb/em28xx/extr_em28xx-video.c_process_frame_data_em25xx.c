#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct em28xx_v4l2 {int top_field; } ;
struct em28xx_dmaqueue {int dummy; } ;
struct em28xx_buffer {int dummy; } ;
struct TYPE_2__ {struct em28xx_buffer* vid_buf; } ;
struct em28xx {TYPE_1__ usb_ctl; scalar_t__ analog_xfer_bulk; struct em28xx_v4l2* v4l2; struct em28xx_dmaqueue vidq; } ;

/* Variables and functions */
 unsigned char EM25XX_FRMDATAHDR_BYTE1 ; 
 unsigned char EM25XX_FRMDATAHDR_BYTE2_FRAME_END ; 
 unsigned char EM25XX_FRMDATAHDR_BYTE2_FRAME_ID ; 
 unsigned char EM25XX_FRMDATAHDR_BYTE2_MASK ; 
 int /*<<< orphan*/  em28xx_copy_video (struct em28xx*,struct em28xx_buffer*,unsigned char*,unsigned int) ; 
 struct em28xx_buffer* finish_field_prepare_next (struct em28xx*,struct em28xx_buffer*,struct em28xx_dmaqueue*) ; 

__attribute__((used)) static inline void process_frame_data_em25xx(struct em28xx *dev,
					     unsigned char *data_pkt,
					     unsigned int  data_len)
{
	struct em28xx_buffer    *buf = dev->usb_ctl.vid_buf;
	struct em28xx_dmaqueue  *dmaq = &dev->vidq;
	struct em28xx_v4l2      *v4l2 = dev->v4l2;
	bool frame_end = false;

	/* Check for header */
	/*
	 * NOTE: at least with bulk transfers, only the first packet
	 * has a header and has always set the FRAME_END bit
	 */
	if (data_len >= 2) {	/* em25xx header is only 2 bytes long */
		if ((data_pkt[0] == EM25XX_FRMDATAHDR_BYTE1) &&
		    ((data_pkt[1] & ~EM25XX_FRMDATAHDR_BYTE2_MASK) == 0x00)) {
			v4l2->top_field = !(data_pkt[1] &
					   EM25XX_FRMDATAHDR_BYTE2_FRAME_ID);
			frame_end = data_pkt[1] &
				    EM25XX_FRMDATAHDR_BYTE2_FRAME_END;
			data_pkt += 2;
			data_len -= 2;
		}

		/* Finish field and prepare next (BULK only) */
		if (dev->analog_xfer_bulk && frame_end) {
			buf = finish_field_prepare_next(dev, buf, dmaq);
			dev->usb_ctl.vid_buf = buf;
		}
		/*
		 * NOTE: in ISOC mode when a new frame starts and buf==NULL,
		 * we COULD already prepare a buffer here to avoid skipping the
		 * first frame.
		 */
	}

	/* Copy data */
	if (buf && data_len > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_len);

	/* Finish frame (ISOC only) => avoids lag of 1 frame */
	if (!dev->analog_xfer_bulk && frame_end) {
		buf = finish_field_prepare_next(dev, buf, dmaq);
		dev->usb_ctl.vid_buf = buf;
	}

	/*
	 * NOTES:
	 *
	 * 1) Tested with USB bulk transfers only !
	 * The wording in the datasheet suggests that isoc might work different.
	 * The current code assumes that with isoc transfers each packet has a
	 * header like with the other em28xx devices.
	 *
	 * 2) Support for interlaced mode is pure theory. It has not been
	 * tested and it is unknown if these devices actually support it.
	 */
}