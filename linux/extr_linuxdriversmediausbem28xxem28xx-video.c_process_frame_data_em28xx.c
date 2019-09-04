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
struct em28xx_v4l2 {int capture_type; unsigned int vbi_read; int top_field; int vbi_width; int vbi_height; } ;
struct em28xx_dmaqueue {int dummy; } ;
struct em28xx_buffer {int dummy; } ;
struct TYPE_2__ {struct em28xx_buffer* vid_buf; struct em28xx_buffer* vbi_buf; } ;
struct em28xx {TYPE_1__ usb_ctl; struct em28xx_dmaqueue vbiq; struct em28xx_dmaqueue vidq; struct em28xx_v4l2* v4l2; } ;

/* Variables and functions */
 int /*<<< orphan*/  em28xx_copy_vbi (struct em28xx*,struct em28xx_buffer*,unsigned char*,int) ; 
 int /*<<< orphan*/  em28xx_copy_video (struct em28xx*,struct em28xx_buffer*,unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  em28xx_isocdbg (char*) ; 
 struct em28xx_buffer* finish_field_prepare_next (struct em28xx*,struct em28xx_buffer*,struct em28xx_dmaqueue*) ; 

__attribute__((used)) static inline void process_frame_data_em28xx(struct em28xx *dev,
					     unsigned char *data_pkt,
					     unsigned int  data_len)
{
	struct em28xx_v4l2      *v4l2 = dev->v4l2;
	struct em28xx_buffer    *buf = dev->usb_ctl.vid_buf;
	struct em28xx_buffer    *vbi_buf = dev->usb_ctl.vbi_buf;
	struct em28xx_dmaqueue  *dma_q = &dev->vidq;
	struct em28xx_dmaqueue  *vbi_dma_q = &dev->vbiq;

	/*
	 * capture type 0 = vbi start
	 * capture type 1 = vbi in progress
	 * capture type 2 = video start
	 * capture type 3 = video in progress
	 */
	if (data_len >= 4) {
		/*
		 * NOTE: Headers are always 4 bytes and
		 * never split across packets
		 */
		if (data_pkt[0] == 0x88 && data_pkt[1] == 0x88 &&
		    data_pkt[2] == 0x88 && data_pkt[3] == 0x88) {
			/* Continuation */
			data_pkt += 4;
			data_len -= 4;
		} else if (data_pkt[0] == 0x33 && data_pkt[1] == 0x95) {
			/* Field start (VBI mode) */
			v4l2->capture_type = 0;
			v4l2->vbi_read = 0;
			em28xx_isocdbg("VBI START HEADER !!!\n");
			v4l2->top_field = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_len -= 4;
		} else if (data_pkt[0] == 0x22 && data_pkt[1] == 0x5a) {
			/* Field start (VBI disabled) */
			v4l2->capture_type = 2;
			em28xx_isocdbg("VIDEO START HEADER !!!\n");
			v4l2->top_field = !(data_pkt[2] & 1);
			data_pkt += 4;
			data_len -= 4;
		}
	}
	/*
	 * NOTE: With bulk transfers, intermediate data packets
	 * have no continuation header
	 */

	if (v4l2->capture_type == 0) {
		vbi_buf = finish_field_prepare_next(dev, vbi_buf, vbi_dma_q);
		dev->usb_ctl.vbi_buf = vbi_buf;
		v4l2->capture_type = 1;
	}

	if (v4l2->capture_type == 1) {
		int vbi_size = v4l2->vbi_width * v4l2->vbi_height;
		int vbi_data_len = ((v4l2->vbi_read + data_len) > vbi_size) ?
				   (vbi_size - v4l2->vbi_read) : data_len;

		/* Copy VBI data */
		if (vbi_buf)
			em28xx_copy_vbi(dev, vbi_buf, data_pkt, vbi_data_len);
		v4l2->vbi_read += vbi_data_len;

		if (vbi_data_len < data_len) {
			/* Continue with copying video data */
			v4l2->capture_type = 2;
			data_pkt += vbi_data_len;
			data_len -= vbi_data_len;
		}
	}

	if (v4l2->capture_type == 2) {
		buf = finish_field_prepare_next(dev, buf, dma_q);
		dev->usb_ctl.vid_buf = buf;
		v4l2->capture_type = 3;
	}

	if (v4l2->capture_type == 3 && buf && data_len > 0)
		em28xx_copy_video(dev, buf, data_pkt, data_len);
}