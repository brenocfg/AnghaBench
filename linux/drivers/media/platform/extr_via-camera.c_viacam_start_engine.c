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
struct via_camera {TYPE_1__* viadev; int /*<<< orphan*/  opstate; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_RUNNING ; 
 int /*<<< orphan*/  VCR_CAPINTC ; 
 int /*<<< orphan*/  VCR_CI_ENABLE ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  viacam_int_enable (struct via_camera*) ; 
 int /*<<< orphan*/  viacam_read_reg (struct via_camera*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  viacam_write_reg_mask (struct via_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void viacam_start_engine(struct via_camera *cam)
{
	spin_lock_irq(&cam->viadev->reg_lock);
	viacam_write_reg_mask(cam, VCR_CAPINTC, VCR_CI_ENABLE, VCR_CI_ENABLE);
	viacam_int_enable(cam);
	(void) viacam_read_reg(cam, VCR_CAPINTC); /* Force post */
	cam->opstate = S_RUNNING;
	spin_unlock_irq(&cam->viadev->reg_lock);
}