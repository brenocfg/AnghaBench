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
struct vsp1_pipeline {int dummy; } ;
struct vsp1_lut {int /*<<< orphan*/  lock; struct vsp1_dl_body* lut; } ;
struct vsp1_entity {int /*<<< orphan*/  subdev; } ;
struct vsp1_dl_list {int dummy; } ;
struct vsp1_dl_body {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vsp1_lut* to_lut (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vsp1_dl_body_put (struct vsp1_dl_body*) ; 
 int /*<<< orphan*/  vsp1_dl_list_add_body (struct vsp1_dl_list*,struct vsp1_dl_body*) ; 

__attribute__((used)) static void lut_configure_frame(struct vsp1_entity *entity,
				struct vsp1_pipeline *pipe,
				struct vsp1_dl_list *dl,
				struct vsp1_dl_body *dlb)
{
	struct vsp1_lut *lut = to_lut(&entity->subdev);
	struct vsp1_dl_body *lut_dlb;
	unsigned long flags;

	spin_lock_irqsave(&lut->lock, flags);
	lut_dlb = lut->lut;
	lut->lut = NULL;
	spin_unlock_irqrestore(&lut->lock, flags);

	if (lut_dlb) {
		vsp1_dl_list_add_body(dl, lut_dlb);

		/* Release our local reference. */
		vsp1_dl_body_put(lut_dlb);
	}
}