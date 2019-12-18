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
typedef  int u32 ;
struct TYPE_2__ {unsigned int active; unsigned int const pending; int /*<<< orphan*/  lock; } ;
struct vsp1_rwpf {int alpha; int outfmt; TYPE_1__ flip; } ;
struct vsp1_pipeline {int dummy; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VI6_WPF_OUTFMT ; 
 int VI6_WPF_OUTFMT_FLP ; 
 int VI6_WPF_OUTFMT_HFLP ; 
 int VI6_WPF_OUTFMT_PDV_SHIFT ; 
 int /*<<< orphan*/  WPF_CTRL_HFLIP ; 
 int /*<<< orphan*/  WPF_CTRL_VFLIP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vsp1_rwpf* to_rwpf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_wpf_write (struct vsp1_rwpf*,struct vsp1_dl_body*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void wpf_configure_frame(struct vsp1_entity *entity,
				struct vsp1_pipeline *pipe,
				struct vsp1_dl_list *dl,
				struct vsp1_dl_body *dlb)
{
	const unsigned int mask = BIT(WPF_CTRL_VFLIP)
				| BIT(WPF_CTRL_HFLIP);
	struct vsp1_rwpf *wpf = to_rwpf(&entity->subdev);
	unsigned long flags;
	u32 outfmt;

	spin_lock_irqsave(&wpf->flip.lock, flags);
	wpf->flip.active = (wpf->flip.active & ~mask)
			 | (wpf->flip.pending & mask);
	spin_unlock_irqrestore(&wpf->flip.lock, flags);

	outfmt = (wpf->alpha << VI6_WPF_OUTFMT_PDV_SHIFT) | wpf->outfmt;

	if (wpf->flip.active & BIT(WPF_CTRL_VFLIP))
		outfmt |= VI6_WPF_OUTFMT_FLP;
	if (wpf->flip.active & BIT(WPF_CTRL_HFLIP))
		outfmt |= VI6_WPF_OUTFMT_HFLP;

	vsp1_wpf_write(wpf, dlb, VI6_WPF_OUTFMT, outfmt);
}