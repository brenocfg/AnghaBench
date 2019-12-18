#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct camif_frame {int f_width; int f_height; } ;
struct camif_vp {int /*<<< orphan*/  offset; int /*<<< orphan*/  id; int /*<<< orphan*/  camif; struct camif_frame out_frame; } ;

/* Variables and functions */
 int CITRGFMT_TARGETSIZE_MASK ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CITRGFMT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int camif_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void camif_hw_set_out_dma_size(struct camif_vp *vp)
{
	struct camif_frame *frame = &vp->out_frame;
	u32 cfg;

	cfg = camif_read(vp->camif, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset));
	cfg &= ~CITRGFMT_TARGETSIZE_MASK;
	cfg |= (frame->f_width << 16) | frame->f_height;
	camif_write(vp->camif, S3C_CAMIF_REG_CITRGFMT(vp->id, vp->offset), cfg);
}