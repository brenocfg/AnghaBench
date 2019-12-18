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
struct TYPE_3__ {scalar_t__ line; scalar_t__ initial; } ;
struct TYPE_4__ {int top; scalar_t__ width; scalar_t__ left; } ;
struct camif_frame {int f_width; TYPE_1__ dma_offset; TYPE_2__ rect; } ;
struct camif_vp {struct camif_frame out_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void camif_prepare_dma_offset(struct camif_vp *vp)
{
	struct camif_frame *f = &vp->out_frame;

	f->dma_offset.initial = f->rect.top * f->f_width + f->rect.left;
	f->dma_offset.line = f->f_width - (f->rect.left + f->rect.width);

	pr_debug("dma_offset: initial: %d, line: %d\n",
		 f->dma_offset.initial, f->dma_offset.line);
}