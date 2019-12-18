#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* frame; } ;
struct s2255_vc {unsigned long last_frame; int width; int height; TYPE_3__* fmt; TYPE_2__ buffer; struct s2255_dev* dev; } ;
struct s2255_dev {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  vb2_buf; } ;
struct s2255_buffer {TYPE_4__ vb; } ;
struct TYPE_7__ {int fourcc; } ;
struct TYPE_5__ {scalar_t__ lpvbits; } ;

/* Variables and functions */
#define  V4L2_PIX_FMT_GREY 133 
#define  V4L2_PIX_FMT_JPEG 132 
#define  V4L2_PIX_FMT_MJPEG 131 
#define  V4L2_PIX_FMT_UYVY 130 
#define  V4L2_PIX_FMT_YUV422P 129 
#define  V4L2_PIX_FMT_YUYV 128 
 int /*<<< orphan*/  dprintk (struct s2255_dev*,int,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  planar422p_to_yuv_packed (unsigned char const*,char*,int,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 char* vb2_plane_vaddr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s2255_fillbuff(struct s2255_vc *vc,
			   struct s2255_buffer *buf, int jpgsize)
{
	int pos = 0;
	const char *tmpbuf;
	char *vbuf = vb2_plane_vaddr(&buf->vb.vb2_buf, 0);
	unsigned long last_frame;
	struct s2255_dev *dev = vc->dev;

	if (!vbuf)
		return;
	last_frame = vc->last_frame;
	if (last_frame != -1) {
		tmpbuf =
		    (const char *)vc->buffer.frame[last_frame].lpvbits;
		switch (vc->fmt->fourcc) {
		case V4L2_PIX_FMT_YUYV:
		case V4L2_PIX_FMT_UYVY:
			planar422p_to_yuv_packed((const unsigned char *)tmpbuf,
						 vbuf, vc->width,
						 vc->height,
						 vc->fmt->fourcc);
			break;
		case V4L2_PIX_FMT_GREY:
			memcpy(vbuf, tmpbuf, vc->width * vc->height);
			break;
		case V4L2_PIX_FMT_JPEG:
		case V4L2_PIX_FMT_MJPEG:
			vb2_set_plane_payload(&buf->vb.vb2_buf, 0, jpgsize);
			memcpy(vbuf, tmpbuf, jpgsize);
			break;
		case V4L2_PIX_FMT_YUV422P:
			memcpy(vbuf, tmpbuf,
			       vc->width * vc->height * 2);
			break;
		default:
			pr_info("s2255: unknown format?\n");
		}
		vc->last_frame = -1;
	} else {
		pr_err("s2255: =======no frame\n");
		return;
	}
	dprintk(dev, 2, "s2255fill at : Buffer %p size= %d\n",
		vbuf, pos);
}