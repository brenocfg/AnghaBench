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
struct vsp1_lut {int /*<<< orphan*/  lock; int /*<<< orphan*/  lut; int /*<<< orphan*/  pool; } ;
struct vsp1_dl_body {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * p_u32; } ;
struct v4l2_ctrl {TYPE_1__ p_new; } ;

/* Variables and functions */
 int ENOMEM ; 
 unsigned int LUT_SIZE ; 
 scalar_t__ VI6_LUT_TABLE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,struct vsp1_dl_body*) ; 
 struct vsp1_dl_body* vsp1_dl_body_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsp1_dl_body_put (struct vsp1_dl_body*) ; 
 int /*<<< orphan*/  vsp1_dl_body_write (struct vsp1_dl_body*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lut_set_table(struct vsp1_lut *lut, struct v4l2_ctrl *ctrl)
{
	struct vsp1_dl_body *dlb;
	unsigned int i;

	dlb = vsp1_dl_body_get(lut->pool);
	if (!dlb)
		return -ENOMEM;

	for (i = 0; i < LUT_SIZE; ++i)
		vsp1_dl_body_write(dlb, VI6_LUT_TABLE + 4 * i,
				       ctrl->p_new.p_u32[i]);

	spin_lock_irq(&lut->lock);
	swap(lut->lut, dlb);
	spin_unlock_irq(&lut->lock);

	vsp1_dl_body_put(dlb);
	return 0;
}