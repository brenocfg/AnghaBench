#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vb2_queue {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  reserved; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  pixelformat; } ;
struct TYPE_6__ {TYPE_1__ sdr; } ;
struct v4l2_format {TYPE_2__ fmt; } ;
struct rcar_drif_sdr {scalar_t__ num_hw_ch; scalar_t__ num_cur_ch; int /*<<< orphan*/  cur_ch_mask; int /*<<< orphan*/  hw_ch_mask; TYPE_3__* fmt; struct vb2_queue vb_queue; } ;
struct file {int dummy; } ;
struct TYPE_7__ {scalar_t__ num_ch; int /*<<< orphan*/  buffersize; int /*<<< orphan*/  pixelformat; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_3__*) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 TYPE_3__* formats ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdrif_dbg (struct rcar_drif_sdr*,char*,unsigned int,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ vb2_is_busy (struct vb2_queue*) ; 
 struct rcar_drif_sdr* video_drvdata (struct file*) ; 

__attribute__((used)) static int rcar_drif_s_fmt_sdr_cap(struct file *file, void *priv,
				   struct v4l2_format *f)
{
	struct rcar_drif_sdr *sdr = video_drvdata(file);
	struct vb2_queue *q = &sdr->vb_queue;
	unsigned int i;

	if (vb2_is_busy(q))
		return -EBUSY;

	for (i = 0; i < ARRAY_SIZE(formats); i++) {
		if (formats[i].pixelformat == f->fmt.sdr.pixelformat)
			break;
	}

	if (i == ARRAY_SIZE(formats))
		i = 0;		/* Set the 1st format as default on no match */

	sdr->fmt = &formats[i];
	f->fmt.sdr.pixelformat = sdr->fmt->pixelformat;
	f->fmt.sdr.buffersize = formats[i].buffersize;
	memset(f->fmt.sdr.reserved, 0, sizeof(f->fmt.sdr.reserved));

	/*
	 * If a format demands one channel only out of two
	 * enabled channels, pick the 0th channel.
	 */
	if (formats[i].num_ch < sdr->num_hw_ch) {
		sdr->cur_ch_mask = BIT(0);
		sdr->num_cur_ch = formats[i].num_ch;
	} else {
		sdr->cur_ch_mask = sdr->hw_ch_mask;
		sdr->num_cur_ch = sdr->num_hw_ch;
	}

	rdrif_dbg(sdr, "cur: idx %u mask %lu num %u\n",
		  i, sdr->cur_ch_mask, sdr->num_cur_ch);

	return 0;
}