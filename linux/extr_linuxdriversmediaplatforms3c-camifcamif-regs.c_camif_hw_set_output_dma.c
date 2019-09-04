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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  width; } ;
struct camif_dma_offset {int /*<<< orphan*/  line; int /*<<< orphan*/  initial; } ;
struct camif_frame {TYPE_2__ rect; struct camif_dma_offset dma_offset; } ;
struct camif_vp {int /*<<< orphan*/  offset; int /*<<< orphan*/  id; struct camif_fmt* out_fmt; struct camif_frame out_frame; struct camif_dev* camif; } ;
struct camif_fmt {int /*<<< orphan*/  ybpp; } ;
struct camif_dev {TYPE_1__* variant; } ;
struct TYPE_3__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 int CICTRL_BURST_MASK ; 
 int CICTRL_CBURST1 (unsigned int) ; 
 int CICTRL_CBURST2 (unsigned int) ; 
 int CICTRL_YBURST1 (unsigned int) ; 
 int CICTRL_YBURST2 (unsigned int) ; 
 scalar_t__ S3C6410_CAMIF_IP_REV ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CICTRL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CISSCB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CISSCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CISSY (int /*<<< orphan*/ ) ; 
 int S3C_CISS_OFFS_INITIAL (int /*<<< orphan*/ ) ; 
 int S3C_CISS_OFFS_LINE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_get_dma_burst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  camif_hw_set_out_dma_size (struct camif_vp*) ; 
 int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int,unsigned int) ; 

void camif_hw_set_output_dma(struct camif_vp *vp)
{
	struct camif_dev *camif = vp->camif;
	struct camif_frame *frame = &vp->out_frame;
	const struct camif_fmt *fmt = vp->out_fmt;
	unsigned int ymburst = 0, yrburst = 0;
	u32 cfg;

	camif_hw_set_out_dma_size(vp);

	if (camif->variant->ip_revision == S3C6410_CAMIF_IP_REV) {
		struct camif_dma_offset *offset = &frame->dma_offset;
		/* Set the input dma offsets. */
		cfg = S3C_CISS_OFFS_INITIAL(offset->initial);
		cfg |= S3C_CISS_OFFS_LINE(offset->line);
		camif_write(camif, S3C_CAMIF_REG_CISSY(vp->id), cfg);
		camif_write(camif, S3C_CAMIF_REG_CISSCB(vp->id), cfg);
		camif_write(camif, S3C_CAMIF_REG_CISSCR(vp->id), cfg);
	}

	/* Configure DMA burst values */
	camif_get_dma_burst(frame->rect.width, fmt->ybpp, &ymburst, &yrburst);

	cfg = camif_read(camif, S3C_CAMIF_REG_CICTRL(vp->id, vp->offset));
	cfg &= ~CICTRL_BURST_MASK;

	cfg |= CICTRL_YBURST1(ymburst) | CICTRL_YBURST2(yrburst);
	cfg |= CICTRL_CBURST1(ymburst / 2) | CICTRL_CBURST2(yrburst / 2);

	camif_write(camif, S3C_CAMIF_REG_CICTRL(vp->id, vp->offset), cfg);

	pr_debug("ymburst: %u, yrburst: %u\n", ymburst, yrburst);
}