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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct vb2_buffer {int dummy; } ;
struct vb2_v4l2_buffer {struct vb2_buffer vb2_buf; } ;
struct v4l2_rect {int width; int height; } ;
struct coda_q_data {struct v4l2_rect rect; } ;
struct coda_dev {TYPE_2__* devtype; int /*<<< orphan*/  v4l2_dev; } ;
struct coda_ctx {int /*<<< orphan*/  reg_idx; TYPE_1__* codec; struct coda_dev* dev; } ;
struct TYPE_4__ {scalar_t__ product; } ;
struct TYPE_3__ {scalar_t__ dst_fourcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODA9_CMD_ENC_HEADER_FRAME_CROP_H ; 
 int /*<<< orphan*/  CODA9_CMD_ENC_HEADER_FRAME_CROP_V ; 
 int CODA9_HEADER_FRAME_CROP ; 
 scalar_t__ CODA_960 ; 
 int /*<<< orphan*/  CODA_CMD_ENC_HEADER_BB_SIZE ; 
 int /*<<< orphan*/  CODA_CMD_ENC_HEADER_BB_START ; 
 int /*<<< orphan*/  CODA_CMD_ENC_HEADER_CODE ; 
 int /*<<< orphan*/  CODA_COMMAND_ENCODE_HEADER ; 
 int CODA_HEADER_H264_SPS ; 
 int /*<<< orphan*/  CODA_REG_BIT_WR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_BUF_TYPE_VIDEO_OUTPUT ; 
 scalar_t__ V4L2_PIX_FMT_H264 ; 
 int coda_command_sync (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int coda_read (struct coda_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  coda_write (struct coda_dev*,int,int /*<<< orphan*/ ) ; 
 struct coda_q_data* get_q_data (struct coda_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*) ; 
 int vb2_dma_contig_plane_dma_addr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 size_t vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 scalar_t__ vb2_plane_vaddr (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int coda_encode_header(struct coda_ctx *ctx, struct vb2_v4l2_buffer *buf,
			      int header_code, u8 *header, int *size)
{
	struct vb2_buffer *vb = &buf->vb2_buf;
	struct coda_dev *dev = ctx->dev;
	struct coda_q_data *q_data_src;
	struct v4l2_rect *r;
	size_t bufsize;
	int ret;
	int i;

	if (dev->devtype->product == CODA_960)
		memset(vb2_plane_vaddr(vb, 0), 0, 64);

	coda_write(dev, vb2_dma_contig_plane_dma_addr(vb, 0),
		   CODA_CMD_ENC_HEADER_BB_START);
	bufsize = vb2_plane_size(vb, 0);
	if (dev->devtype->product == CODA_960)
		bufsize /= 1024;
	coda_write(dev, bufsize, CODA_CMD_ENC_HEADER_BB_SIZE);
	if (dev->devtype->product == CODA_960 &&
	    ctx->codec->dst_fourcc == V4L2_PIX_FMT_H264 &&
	    header_code == CODA_HEADER_H264_SPS) {
		q_data_src = get_q_data(ctx, V4L2_BUF_TYPE_VIDEO_OUTPUT);
		r = &q_data_src->rect;

		if (r->width % 16 || r->height % 16) {
			u32 crop_right = round_up(r->width, 16) -  r->width;
			u32 crop_bottom = round_up(r->height, 16) - r->height;

			coda_write(dev, crop_right,
				   CODA9_CMD_ENC_HEADER_FRAME_CROP_H);
			coda_write(dev, crop_bottom,
				   CODA9_CMD_ENC_HEADER_FRAME_CROP_V);
			header_code |= CODA9_HEADER_FRAME_CROP;
		}
	}
	coda_write(dev, header_code, CODA_CMD_ENC_HEADER_CODE);
	ret = coda_command_sync(ctx, CODA_COMMAND_ENCODE_HEADER);
	if (ret < 0) {
		v4l2_err(&dev->v4l2_dev, "CODA_COMMAND_ENCODE_HEADER timeout\n");
		return ret;
	}

	if (dev->devtype->product == CODA_960) {
		for (i = 63; i > 0; i--)
			if (((char *)vb2_plane_vaddr(vb, 0))[i] != 0)
				break;
		*size = i + 1;
	} else {
		*size = coda_read(dev, CODA_REG_BIT_WR_PTR(ctx->reg_idx)) -
			coda_read(dev, CODA_CMD_ENC_HEADER_BB_START);
	}
	memcpy(header, vb2_plane_vaddr(vb, 0), *size);

	return 0;
}