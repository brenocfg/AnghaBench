#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {TYPE_1__* planes; } ;
struct TYPE_6__ {TYPE_2__ vb2_buf; } ;
struct go7007_buffer {int frame_offset; int modet_active; TYPE_3__ vb; } ;
struct go7007 {int format; int state; int seen_frame; int parse_length; int modet_word; int /*<<< orphan*/  active_map; int /*<<< orphan*/  modet_enable; struct go7007_buffer* active_buf; int /*<<< orphan*/  v4l2_dev; } ;
struct TYPE_4__ {int bytesused; } ;

/* Variables and functions */
 int GO7007_BUF_SIZE ; 
#define  STATE_00 139 
#define  STATE_00_00 138 
#define  STATE_00_00_01 137 
#define  STATE_DATA 136 
#define  STATE_FF 135 
#define  STATE_MODET_MAP 134 
#define  STATE_UNPARSED 133 
#define  STATE_VBI_LEN_A 132 
#define  STATE_VBI_LEN_B 131 
 int const V4L2_PIX_FMT_MJPEG ; 
#define  V4L2_PIX_FMT_MPEG1 130 
#define  V4L2_PIX_FMT_MPEG2 129 
#define  V4L2_PIX_FMT_MPEG4 128 
 struct go7007_buffer* frame_boundary (struct go7007*,struct go7007_buffer*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  store_byte (struct go7007_buffer*,int) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_bitmap_word (struct go7007*) ; 

void go7007_parse_video_stream(struct go7007 *go, u8 *buf, int length)
{
	struct go7007_buffer *vb = go->active_buf;
	int i, seq_start_code = -1, gop_start_code = -1, frame_start_code = -1;

	switch (go->format) {
	case V4L2_PIX_FMT_MPEG4:
		seq_start_code = 0xB0;
		gop_start_code = 0xB3;
		frame_start_code = 0xB6;
		break;
	case V4L2_PIX_FMT_MPEG1:
	case V4L2_PIX_FMT_MPEG2:
		seq_start_code = 0xB3;
		gop_start_code = 0xB8;
		frame_start_code = 0x00;
		break;
	}

	for (i = 0; i < length; ++i) {
		if (vb && vb->vb.vb2_buf.planes[0].bytesused >=
				GO7007_BUF_SIZE - 3) {
			v4l2_info(&go->v4l2_dev, "dropping oversized frame\n");
			vb->vb.vb2_buf.planes[0].bytesused = 0;
			vb->frame_offset = 0;
			vb->modet_active = 0;
			vb = go->active_buf = NULL;
		}

		switch (go->state) {
		case STATE_DATA:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00;
				break;
			case 0xFF:
				go->state = STATE_FF;
				break;
			default:
				store_byte(vb, buf[i]);
				break;
			}
			break;
		case STATE_00:
			switch (buf[i]) {
			case 0x00:
				go->state = STATE_00_00;
				break;
			case 0xFF:
				store_byte(vb, 0x00);
				go->state = STATE_FF;
				break;
			default:
				store_byte(vb, 0x00);
				store_byte(vb, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_00_00:
			switch (buf[i]) {
			case 0x00:
				store_byte(vb, 0x00);
				/* go->state remains STATE_00_00 */
				break;
			case 0x01:
				go->state = STATE_00_00_01;
				break;
			case 0xFF:
				store_byte(vb, 0x00);
				store_byte(vb, 0x00);
				go->state = STATE_FF;
				break;
			default:
				store_byte(vb, 0x00);
				store_byte(vb, 0x00);
				store_byte(vb, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_00_00_01:
			if (buf[i] == 0xF8 && go->modet_enable == 0) {
				/* MODET start code, but MODET not enabled */
				store_byte(vb, 0x00);
				store_byte(vb, 0x00);
				store_byte(vb, 0x01);
				store_byte(vb, 0xF8);
				go->state = STATE_DATA;
				break;
			}
			/* If this is the start of a new MPEG frame,
			 * get a new buffer */
			if ((go->format == V4L2_PIX_FMT_MPEG1 ||
			     go->format == V4L2_PIX_FMT_MPEG2 ||
			     go->format == V4L2_PIX_FMT_MPEG4) &&
			    (buf[i] == seq_start_code ||
			     buf[i] == gop_start_code ||
			     buf[i] == frame_start_code)) {
				if (vb == NULL || go->seen_frame)
					vb = frame_boundary(go, vb);
				go->seen_frame = buf[i] == frame_start_code;
				if (vb && go->seen_frame)
					vb->frame_offset =
					vb->vb.vb2_buf.planes[0].bytesused;
			}
			/* Handle any special chunk types, or just write the
			 * start code to the (potentially new) buffer */
			switch (buf[i]) {
			case 0xF5: /* timestamp */
				go->parse_length = 12;
				go->state = STATE_UNPARSED;
				break;
			case 0xF6: /* vbi */
				go->state = STATE_VBI_LEN_A;
				break;
			case 0xF8: /* MD map */
				go->parse_length = 0;
				memset(go->active_map, 0,
						sizeof(go->active_map));
				go->state = STATE_MODET_MAP;
				break;
			case 0xFF: /* Potential JPEG start code */
				store_byte(vb, 0x00);
				store_byte(vb, 0x00);
				store_byte(vb, 0x01);
				go->state = STATE_FF;
				break;
			default:
				store_byte(vb, 0x00);
				store_byte(vb, 0x00);
				store_byte(vb, 0x01);
				store_byte(vb, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_FF:
			switch (buf[i]) {
			case 0x00:
				store_byte(vb, 0xFF);
				go->state = STATE_00;
				break;
			case 0xFF:
				store_byte(vb, 0xFF);
				/* go->state remains STATE_FF */
				break;
			case 0xD8:
				if (go->format == V4L2_PIX_FMT_MJPEG)
					vb = frame_boundary(go, vb);
				/* fall through */
			default:
				store_byte(vb, 0xFF);
				store_byte(vb, buf[i]);
				go->state = STATE_DATA;
				break;
			}
			break;
		case STATE_VBI_LEN_A:
			go->parse_length = buf[i] << 8;
			go->state = STATE_VBI_LEN_B;
			break;
		case STATE_VBI_LEN_B:
			go->parse_length |= buf[i];
			if (go->parse_length > 0)
				go->state = STATE_UNPARSED;
			else
				go->state = STATE_DATA;
			break;
		case STATE_MODET_MAP:
			if (go->parse_length < 204) {
				if (go->parse_length & 1) {
					go->modet_word |= buf[i];
					write_bitmap_word(go);
				} else
					go->modet_word = buf[i] << 8;
			} else if (go->parse_length == 207 && vb) {
				vb->modet_active = buf[i];
			}
			if (++go->parse_length == 208)
				go->state = STATE_DATA;
			break;
		case STATE_UNPARSED:
			if (--go->parse_length == 0)
				go->state = STATE_DATA;
			break;
		}
	}
}