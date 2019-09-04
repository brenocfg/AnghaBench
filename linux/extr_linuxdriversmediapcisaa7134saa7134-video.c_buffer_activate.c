#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int dma; } ;
struct saa7134_dmaqueue {int /*<<< orphan*/  timeout; TYPE_4__ pt; } ;
struct saa7134_dev {unsigned long width; unsigned long height; int /*<<< orphan*/  field; TYPE_5__* fmt; } ;
struct TYPE_7__ {TYPE_1__* vb2_queue; } ;
struct TYPE_8__ {TYPE_2__ vb2_buf; } ;
struct saa7134_buf {scalar_t__ top_seen; TYPE_3__ vb2; } ;
struct TYPE_10__ {int depth; unsigned long hshift; unsigned long vshift; scalar_t__ uvswap; scalar_t__ planar; scalar_t__ wswap; scalar_t__ bswap; int /*<<< orphan*/  pm; scalar_t__ yuv; } ;
struct TYPE_6__ {struct saa7134_dmaqueue* drv_priv; } ;

/* Variables and functions */
 scalar_t__ BUFFER_TIMEOUT ; 
 int /*<<< orphan*/  SAA7134_DATA_PATH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAA7134_OFMT_VIDEO_A ; 
 int /*<<< orphan*/  SAA7134_RS_BA1 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_BA2 (int) ; 
 int /*<<< orphan*/  SAA7134_RS_CONTROL (int) ; 
 unsigned long SAA7134_RS_CONTROL_BSWAP ; 
 int SAA7134_RS_CONTROL_BURST_16 ; 
 int SAA7134_RS_CONTROL_ME ; 
 unsigned long SAA7134_RS_CONTROL_WSWAP ; 
 int /*<<< orphan*/  SAA7134_RS_PITCH (int) ; 
 int /*<<< orphan*/  TASK_A ; 
 scalar_t__ V4L2_FIELD_HAS_BOTH (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned long saa7134_buffer_base (struct saa7134_buf*) ; 
 int /*<<< orphan*/  saa7134_set_dmabits (struct saa7134_dev*) ; 
 int /*<<< orphan*/  saa_andorb (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  saa_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa_writel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  set_size (struct saa7134_dev*,int /*<<< orphan*/ ,unsigned long,unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  video_dbg (char*,...) ; 

__attribute__((used)) static int buffer_activate(struct saa7134_dev *dev,
			   struct saa7134_buf *buf,
			   struct saa7134_buf *next)
{
	struct saa7134_dmaqueue *dmaq = buf->vb2.vb2_buf.vb2_queue->drv_priv;
	unsigned long base,control,bpl;
	unsigned long bpl_uv,lines_uv,base2,base3,tmp; /* planar */

	video_dbg("buffer_activate buf=%p\n", buf);
	buf->top_seen = 0;

	set_size(dev, TASK_A, dev->width, dev->height,
		 V4L2_FIELD_HAS_BOTH(dev->field));
	if (dev->fmt->yuv)
		saa_andorb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x03);
	else
		saa_andorb(SAA7134_DATA_PATH(TASK_A), 0x3f, 0x01);
	saa_writeb(SAA7134_OFMT_VIDEO_A, dev->fmt->pm);

	/* DMA: setup channel 0 (= Video Task A0) */
	base  = saa7134_buffer_base(buf);
	if (dev->fmt->planar)
		bpl = dev->width;
	else
		bpl = (dev->width * dev->fmt->depth) / 8;
	control = SAA7134_RS_CONTROL_BURST_16 |
		SAA7134_RS_CONTROL_ME |
		(dmaq->pt.dma >> 12);
	if (dev->fmt->bswap)
		control |= SAA7134_RS_CONTROL_BSWAP;
	if (dev->fmt->wswap)
		control |= SAA7134_RS_CONTROL_WSWAP;
	if (V4L2_FIELD_HAS_BOTH(dev->field)) {
		/* interlaced */
		saa_writel(SAA7134_RS_BA1(0),base);
		saa_writel(SAA7134_RS_BA2(0),base+bpl);
		saa_writel(SAA7134_RS_PITCH(0),bpl*2);
	} else {
		/* non-interlaced */
		saa_writel(SAA7134_RS_BA1(0),base);
		saa_writel(SAA7134_RS_BA2(0),base);
		saa_writel(SAA7134_RS_PITCH(0),bpl);
	}
	saa_writel(SAA7134_RS_CONTROL(0),control);

	if (dev->fmt->planar) {
		/* DMA: setup channel 4+5 (= planar task A) */
		bpl_uv   = bpl >> dev->fmt->hshift;
		lines_uv = dev->height >> dev->fmt->vshift;
		base2    = base + bpl * dev->height;
		base3    = base2 + bpl_uv * lines_uv;
		if (dev->fmt->uvswap)
			tmp = base2, base2 = base3, base3 = tmp;
		video_dbg("uv: bpl=%ld lines=%ld base2/3=%ld/%ld\n",
			bpl_uv,lines_uv,base2,base3);
		if (V4L2_FIELD_HAS_BOTH(dev->field)) {
			/* interlaced */
			saa_writel(SAA7134_RS_BA1(4),base2);
			saa_writel(SAA7134_RS_BA2(4),base2+bpl_uv);
			saa_writel(SAA7134_RS_PITCH(4),bpl_uv*2);
			saa_writel(SAA7134_RS_BA1(5),base3);
			saa_writel(SAA7134_RS_BA2(5),base3+bpl_uv);
			saa_writel(SAA7134_RS_PITCH(5),bpl_uv*2);
		} else {
			/* non-interlaced */
			saa_writel(SAA7134_RS_BA1(4),base2);
			saa_writel(SAA7134_RS_BA2(4),base2);
			saa_writel(SAA7134_RS_PITCH(4),bpl_uv);
			saa_writel(SAA7134_RS_BA1(5),base3);
			saa_writel(SAA7134_RS_BA2(5),base3);
			saa_writel(SAA7134_RS_PITCH(5),bpl_uv);
		}
		saa_writel(SAA7134_RS_CONTROL(4),control);
		saa_writel(SAA7134_RS_CONTROL(5),control);
	}

	/* start DMA */
	saa7134_set_dmabits(dev);
	mod_timer(&dmaq->timeout, jiffies + BUFFER_TIMEOUT);
	return 0;
}