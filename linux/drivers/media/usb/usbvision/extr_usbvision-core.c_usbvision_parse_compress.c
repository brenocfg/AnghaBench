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
struct TYPE_2__ {int format; } ;
struct usbvision_frame {int frmwidth; int frmheight; unsigned char* data; int width; int curline; int v4l2_linesize; TYPE_1__ v4l2_format; } ;
struct usb_usbvision {unsigned char* intra_frame_buffer; int block_pos; int max_strip_len; int comprblock_pos; int /*<<< orphan*/  strip_len_errors; int /*<<< orphan*/  strip_line_number_errors; int /*<<< orphan*/  strip_magic_errors; struct usbvision_frame* cur_frame; } ;
typedef  enum parse_state { ____Placeholder_parse_state } parse_state ;

/* Variables and functions */
 int MAX_FRAME_WIDTH ; 
 int USBVISION_STRIP_HEADER_LEN ; 
 int USBVISION_STRIP_LEN_MAX ; 
 unsigned char USBVISION_STRIP_MAGIC ; 
#define  V4L2_PIX_FMT_GREY 132 
#define  V4L2_PIX_FMT_RGB24 131 
#define  V4L2_PIX_FMT_RGB32 130 
#define  V4L2_PIX_FMT_RGB555 129 
#define  V4L2_PIX_FMT_RGB565 128 
 int V4L2_PIX_FMT_YUV422P ; 
 int V4L2_PIX_FMT_YUYV ; 
 int V4L2_PIX_FMT_YVU420 ; 
 int /*<<< orphan*/  YUV_TO_RGB_BY_THE_BOOK (unsigned char,unsigned char,unsigned char,unsigned char,unsigned char,unsigned char) ; 
 int parse_state_continue ; 
 int parse_state_next_frame ; 
 int parse_state_out ; 
 int /*<<< orphan*/  scratch_get (struct usb_usbvision*,unsigned char*,int) ; 
 int /*<<< orphan*/  scratch_get_extra (struct usb_usbvision*,unsigned char*,int*,int) ; 
 int scratch_len (struct usb_usbvision*) ; 
 int /*<<< orphan*/  scratch_set_extra_ptr (struct usb_usbvision*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbvision_adjust_compression (struct usb_usbvision*) ; 
 int /*<<< orphan*/  usbvision_decompress (struct usb_usbvision*,unsigned char*,unsigned char*,int*,int*,int) ; 
 int /*<<< orphan*/  usbvision_request_intra (struct usb_usbvision*) ; 

__attribute__((used)) static enum parse_state usbvision_parse_compress(struct usb_usbvision *usbvision,
					   long *pcopylen)
{
#define USBVISION_STRIP_MAGIC		0x5A
#define USBVISION_STRIP_LEN_MAX		400
#define USBVISION_STRIP_HEADER_LEN	3

	struct usbvision_frame *frame;
	unsigned char *f, *u = NULL, *v = NULL;
	unsigned char strip_data[USBVISION_STRIP_LEN_MAX];
	unsigned char strip_header[USBVISION_STRIP_HEADER_LEN];
	int idx, idx_end, strip_len, strip_ptr, startblock_pos, block_pos, block_type_pos;
	int clipmask_index;
	int image_size;
	unsigned char rv, gv, bv;
	static unsigned char *Y, *U, *V;

	frame = usbvision->cur_frame;
	image_size = frame->frmwidth * frame->frmheight;
	if ((frame->v4l2_format.format == V4L2_PIX_FMT_YUV422P) ||
	    (frame->v4l2_format.format == V4L2_PIX_FMT_YVU420)) {       /* this is a planar format */
		/* ... v4l2_linesize not used here. */
		f = frame->data + (frame->width * frame->curline);
	} else
		f = frame->data + (frame->v4l2_linesize * frame->curline);

	if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) { /* initialise u and v pointers */
		/* get base of u and b planes add halfoffset */
		u = frame->data
			+ image_size
			+ (frame->frmwidth >> 1) * frame->curline;
		v = u + (image_size >> 1);
	} else if (frame->v4l2_format.format == V4L2_PIX_FMT_YVU420) {
		v = frame->data + image_size + ((frame->curline * (frame->width)) >> 2);
		u = v + (image_size >> 2);
	}

	if (frame->curline == 0)
		usbvision_adjust_compression(usbvision);

	if (scratch_len(usbvision) < USBVISION_STRIP_HEADER_LEN)
		return parse_state_out;

	/* get strip header without changing the scratch_read_ptr */
	scratch_set_extra_ptr(usbvision, &strip_ptr, 0);
	scratch_get_extra(usbvision, &strip_header[0], &strip_ptr,
				USBVISION_STRIP_HEADER_LEN);

	if (strip_header[0] != USBVISION_STRIP_MAGIC) {
		/* wrong strip magic */
		usbvision->strip_magic_errors++;
		return parse_state_next_frame;
	}

	if (frame->curline != (int)strip_header[2]) {
		/* line number mismatch error */
		usbvision->strip_line_number_errors++;
	}

	strip_len = 2 * (unsigned int)strip_header[1];
	if (strip_len > USBVISION_STRIP_LEN_MAX) {
		/* strip overrun */
		/* I think this never happens */
		usbvision_request_intra(usbvision);
	}

	if (scratch_len(usbvision) < strip_len) {
		/* there is not enough data for the strip */
		return parse_state_out;
	}

	if (usbvision->intra_frame_buffer) {
		Y = usbvision->intra_frame_buffer + frame->frmwidth * frame->curline;
		U = usbvision->intra_frame_buffer + image_size + (frame->frmwidth / 2) * (frame->curline / 2);
		V = usbvision->intra_frame_buffer + image_size / 4 * 5 + (frame->frmwidth / 2) * (frame->curline / 2);
	} else {
		return parse_state_next_frame;
	}

	clipmask_index = frame->curline * MAX_FRAME_WIDTH;

	scratch_get(usbvision, strip_data, strip_len);

	idx_end = frame->frmwidth;
	block_type_pos = USBVISION_STRIP_HEADER_LEN;
	startblock_pos = block_type_pos + (idx_end - 1) / 96 + (idx_end / 2 - 1) / 96 + 2;
	block_pos = startblock_pos;

	usbvision->block_pos = block_pos;

	usbvision_decompress(usbvision, strip_data, Y, &block_pos, &block_type_pos, idx_end);
	if (strip_len > usbvision->max_strip_len)
		usbvision->max_strip_len = strip_len;

	if (frame->curline % 2)
		usbvision_decompress(usbvision, strip_data, V, &block_pos, &block_type_pos, idx_end / 2);
	else
		usbvision_decompress(usbvision, strip_data, U, &block_pos, &block_type_pos, idx_end / 2);

	if (block_pos > usbvision->comprblock_pos)
		usbvision->comprblock_pos = block_pos;
	if (block_pos > strip_len)
		usbvision->strip_len_errors++;

	for (idx = 0; idx < idx_end; idx++) {
		if (frame->v4l2_format.format == V4L2_PIX_FMT_YUYV) {
			*f++ = Y[idx];
			*f++ = idx & 0x01 ? U[idx / 2] : V[idx / 2];
		} else if (frame->v4l2_format.format == V4L2_PIX_FMT_YUV422P) {
			*f++ = Y[idx];
			if (idx & 0x01)
				*u++ = U[idx >> 1];
			else
				*v++ = V[idx >> 1];
		} else if (frame->v4l2_format.format == V4L2_PIX_FMT_YVU420) {
			*f++ = Y[idx];
			if (!((idx & 0x01) | (frame->curline & 0x01))) {
				/* only need do this for 1 in 4 pixels */
				/* intraframe buffer is YUV420 format */
				*u++ = U[idx >> 1];
				*v++ = V[idx >> 1];
			}
		} else {
			YUV_TO_RGB_BY_THE_BOOK(Y[idx], U[idx / 2], V[idx / 2], rv, gv, bv);
			switch (frame->v4l2_format.format) {
			case V4L2_PIX_FMT_GREY:
				*f++ = Y[idx];
				break;
			case V4L2_PIX_FMT_RGB555:
				*f++ = (0x1F & rv) |
					(0xE0 & (gv << 5));
				*f++ = (0x03 & (gv >> 3)) |
					(0x7C & (bv << 2));
				break;
			case V4L2_PIX_FMT_RGB565:
				*f++ = (0x1F & rv) |
					(0xE0 & (gv << 5));
				*f++ = (0x07 & (gv >> 3)) |
					(0xF8 & bv);
				break;
			case V4L2_PIX_FMT_RGB24:
				*f++ = rv;
				*f++ = gv;
				*f++ = bv;
				break;
			case V4L2_PIX_FMT_RGB32:
				*f++ = rv;
				*f++ = gv;
				*f++ = bv;
				f++;
				break;
			}
		}
		clipmask_index++;
	}
	/* Deal with non-integer no. of bytes for YUV420P */
	if (frame->v4l2_format.format != V4L2_PIX_FMT_YVU420)
		*pcopylen += frame->v4l2_linesize;
	else
		*pcopylen += frame->curline & 0x01 ? frame->v4l2_linesize : frame->v4l2_linesize << 1;

	frame->curline += 1;

	if (frame->curline >= frame->frmheight)
		return parse_state_next_frame;
	return parse_state_continue;

}