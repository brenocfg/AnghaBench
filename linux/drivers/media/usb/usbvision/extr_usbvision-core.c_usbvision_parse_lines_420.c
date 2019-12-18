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
struct TYPE_4__ {int bytes_per_pixel; int format; } ;
struct TYPE_3__ {unsigned int frame_width; } ;
struct usbvision_frame {unsigned char* data; int v4l2_linesize; int curline; int frmheight; TYPE_2__ v4l2_format; TYPE_1__ isoc_header; } ;
struct usb_usbvision {int stretch_height; int stretch_width; struct usbvision_frame* cur_frame; } ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;

/* Variables and functions */
 int LIMIT_RGB (int) ; 
 int MAX_FRAME_WIDTH ; 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB32 130 
#define  V4L2_PIX_FMT_RGB555 129 
#define  V4L2_PIX_FMT_RGB565 128 
 int V4L2_PIX_FMT_YUYV ; 
 int parse_state_continue ; 
 int parse_state_next_frame ; 
 int parse_state_out ; 
 int /*<<< orphan*/  scratch_get (struct usb_usbvision*,unsigned char*,int) ; 
 int /*<<< orphan*/  scratch_get_extra (struct usb_usbvision*,unsigned char*,int*,int) ; 
 int /*<<< orphan*/  scratch_inc_extra_ptr (int*,int const) ; 
 int scratch_len (struct usb_usbvision*) ; 
 int /*<<< orphan*/  scratch_rm_old (struct usb_usbvision*,int const) ; 
 int /*<<< orphan*/  scratch_set_extra_ptr (struct usb_usbvision*,int*,int const) ; 

__attribute__((used)) static enum parse_state usbvision_parse_lines_420(struct usb_usbvision *usbvision,
					   long *pcopylen)
{
	struct usbvision_frame *frame;
	unsigned char *f_even = NULL, *f_odd = NULL;
	unsigned int pixel_per_line, block;
	int pixel, block_split;
	int y_ptr, u_ptr, v_ptr, y_odd_offset;
	const int y_block_size = 128;
	const int uv_block_size = 64;
	const int sub_block_size = 32;
	const int y_step[] = { 0, 0, 0, 2 }, y_step_size = 4;
	const int uv_step[] = { 0, 0, 0, 4 }, uv_step_size = 4;
	unsigned char y[2], u, v;	/* YUV components */
	int y_, u_, v_, vb, uvg, ur;
	int r_, g_, b_;			/* RGB components */
	unsigned char g;
	int clipmask_even_index, clipmask_odd_index, bytes_per_pixel;
	int clipmask_add, stretch_bytes;

	frame  = usbvision->cur_frame;
	f_even = frame->data + (frame->v4l2_linesize * frame->curline);
	f_odd  = f_even + frame->v4l2_linesize * usbvision->stretch_height;

	/* Make sure there's enough data for the entire line */
	/* In this mode usbvision transfer 3 bytes for every 2 pixels */
	/* I need two lines to decode the color */
	bytes_per_pixel = frame->v4l2_format.bytes_per_pixel;
	stretch_bytes = (usbvision->stretch_width - 1) * bytes_per_pixel;
	clipmask_even_index = frame->curline * MAX_FRAME_WIDTH;
	clipmask_odd_index  = clipmask_even_index + MAX_FRAME_WIDTH;
	clipmask_add = usbvision->stretch_width;
	pixel_per_line = frame->isoc_header.frame_width;

	if (scratch_len(usbvision) < (int)pixel_per_line * 3) {
		/* printk(KERN_DEBUG "out of data, need %d\n", len); */
		return parse_state_out;
	}

	if ((frame->curline + 1) >= frame->frmheight)
		return parse_state_next_frame;

	block_split = (pixel_per_line%y_block_size) ? 1 : 0;	/* are some blocks split into different lines? */

	y_odd_offset = (pixel_per_line / y_block_size) * (y_block_size + uv_block_size)
			+ block_split * uv_block_size;

	scratch_set_extra_ptr(usbvision, &y_ptr, y_odd_offset);
	scratch_set_extra_ptr(usbvision, &u_ptr, y_block_size);
	scratch_set_extra_ptr(usbvision, &v_ptr, y_odd_offset
			+ (4 - block_split) * sub_block_size);

	for (block = 0; block < (pixel_per_line / sub_block_size); block++) {
		for (pixel = 0; pixel < sub_block_size; pixel += 2) {
			scratch_get(usbvision, &y[0], 2);
			scratch_get_extra(usbvision, &u, &u_ptr, 1);
			scratch_get_extra(usbvision, &v, &v_ptr, 1);

			/* I don't use the YUV_TO_RGB macro for better performance */
			v_ = v - 128;
			u_ = u - 128;
			vb = 132252 * v_;
			uvg = -53281 * u_ - 25625 * v_;
			ur = 104595 * u_;

			if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) {
				*f_even++ = y[0];
				*f_even++ = v;
			} else {
				y_ = 76284 * (y[0] - 16);

				b_ = (y_ + vb) >> 16;
				g_ = (y_ + uvg) >> 16;
				r_ = (y_ + ur) >> 16;

				switch (frame->v4l2_format.format) {
				case V4L2_PIX_FMT_RGB565:
					g = LIMIT_RGB(g_);
					*f_even++ =
						(0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_even++ =
						(0x07 & (g >> 3)) |
						(0xF8 &  LIMIT_RGB(b_));
					break;
				case V4L2_PIX_FMT_RGB24:
					*f_even++ = LIMIT_RGB(r_);
					*f_even++ = LIMIT_RGB(g_);
					*f_even++ = LIMIT_RGB(b_);
					break;
				case V4L2_PIX_FMT_RGB32:
					*f_even++ = LIMIT_RGB(r_);
					*f_even++ = LIMIT_RGB(g_);
					*f_even++ = LIMIT_RGB(b_);
					f_even++;
					break;
				case V4L2_PIX_FMT_RGB555:
					g = LIMIT_RGB(g_);
					*f_even++ = (0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_even++ = (0x03 & (g >> 3)) |
						(0x7C & (LIMIT_RGB(b_) << 2));
					break;
				}
			}
			clipmask_even_index += clipmask_add;
			f_even += stretch_bytes;

			if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) {
				*f_even++ = y[1];
				*f_even++ = u;
			} else {
				y_ = 76284 * (y[1] - 16);

				b_ = (y_ + vb) >> 16;
				g_ = (y_ + uvg) >> 16;
				r_ = (y_ + ur) >> 16;

				switch (frame->v4l2_format.format) {
				case V4L2_PIX_FMT_RGB565:
					g = LIMIT_RGB(g_);
					*f_even++ =
						(0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_even++ =
						(0x07 & (g >> 3)) |
						(0xF8 &  LIMIT_RGB(b_));
					break;
				case V4L2_PIX_FMT_RGB24:
					*f_even++ = LIMIT_RGB(r_);
					*f_even++ = LIMIT_RGB(g_);
					*f_even++ = LIMIT_RGB(b_);
					break;
				case V4L2_PIX_FMT_RGB32:
					*f_even++ = LIMIT_RGB(r_);
					*f_even++ = LIMIT_RGB(g_);
					*f_even++ = LIMIT_RGB(b_);
					f_even++;
					break;
				case V4L2_PIX_FMT_RGB555:
					g = LIMIT_RGB(g_);
					*f_even++ = (0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_even++ = (0x03 & (g >> 3)) |
						(0x7C & (LIMIT_RGB(b_) << 2));
					break;
				}
			}
			clipmask_even_index += clipmask_add;
			f_even += stretch_bytes;

			scratch_get_extra(usbvision, &y[0], &y_ptr, 2);

			if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) {
				*f_odd++ = y[0];
				*f_odd++ = v;
			} else {
				y_ = 76284 * (y[0] - 16);

				b_ = (y_ + vb) >> 16;
				g_ = (y_ + uvg) >> 16;
				r_ = (y_ + ur) >> 16;

				switch (frame->v4l2_format.format) {
				case V4L2_PIX_FMT_RGB565:
					g = LIMIT_RGB(g_);
					*f_odd++ =
						(0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_odd++ =
						(0x07 & (g >> 3)) |
						(0xF8 &  LIMIT_RGB(b_));
					break;
				case V4L2_PIX_FMT_RGB24:
					*f_odd++ = LIMIT_RGB(r_);
					*f_odd++ = LIMIT_RGB(g_);
					*f_odd++ = LIMIT_RGB(b_);
					break;
				case V4L2_PIX_FMT_RGB32:
					*f_odd++ = LIMIT_RGB(r_);
					*f_odd++ = LIMIT_RGB(g_);
					*f_odd++ = LIMIT_RGB(b_);
					f_odd++;
					break;
				case V4L2_PIX_FMT_RGB555:
					g = LIMIT_RGB(g_);
					*f_odd++ = (0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_odd++ = (0x03 & (g >> 3)) |
						(0x7C & (LIMIT_RGB(b_) << 2));
					break;
				}
			}
			clipmask_odd_index += clipmask_add;
			f_odd += stretch_bytes;

			if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) {
				*f_odd++ = y[1];
				*f_odd++ = u;
			} else {
				y_ = 76284 * (y[1] - 16);

				b_ = (y_ + vb) >> 16;
				g_ = (y_ + uvg) >> 16;
				r_ = (y_ + ur) >> 16;

				switch (frame->v4l2_format.format) {
				case V4L2_PIX_FMT_RGB565:
					g = LIMIT_RGB(g_);
					*f_odd++ =
						(0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_odd++ =
						(0x07 & (g >> 3)) |
						(0xF8 &  LIMIT_RGB(b_));
					break;
				case V4L2_PIX_FMT_RGB24:
					*f_odd++ = LIMIT_RGB(r_);
					*f_odd++ = LIMIT_RGB(g_);
					*f_odd++ = LIMIT_RGB(b_);
					break;
				case V4L2_PIX_FMT_RGB32:
					*f_odd++ = LIMIT_RGB(r_);
					*f_odd++ = LIMIT_RGB(g_);
					*f_odd++ = LIMIT_RGB(b_);
					f_odd++;
					break;
				case V4L2_PIX_FMT_RGB555:
					g = LIMIT_RGB(g_);
					*f_odd++ = (0x1F & LIMIT_RGB(r_)) |
						(0xE0 & (g << 5));
					*f_odd++ = (0x03 & (g >> 3)) |
						(0x7C & (LIMIT_RGB(b_) << 2));
					break;
				}
			}
			clipmask_odd_index += clipmask_add;
			f_odd += stretch_bytes;
		}

		scratch_rm_old(usbvision, y_step[block % y_step_size] * sub_block_size);
		scratch_inc_extra_ptr(&y_ptr, y_step[(block + 2 * block_split) % y_step_size]
				* sub_block_size);
		scratch_inc_extra_ptr(&u_ptr, uv_step[block % uv_step_size]
				* sub_block_size);
		scratch_inc_extra_ptr(&v_ptr, uv_step[(block + 2 * block_split) % uv_step_size]
				* sub_block_size);
	}

	scratch_rm_old(usbvision, pixel_per_line * 3 / 2
			+ block_split * sub_block_size);

	frame->curline += 2 * usbvision->stretch_height;
	*pcopylen += frame->v4l2_linesize * 2 * usbvision->stretch_height;

	if (frame->curline >= frame->frmheight)
		return parse_state_next_frame;
	return parse_state_continue;
}