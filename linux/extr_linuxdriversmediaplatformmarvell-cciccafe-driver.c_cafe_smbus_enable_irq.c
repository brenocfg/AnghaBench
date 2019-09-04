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
struct TYPE_2__ {int /*<<< orphan*/  dev_lock; } ;
struct cafe_camera {TYPE_1__ mcam; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IRQMASK ; 
 int /*<<< orphan*/  TWSIIRQS ; 
 int /*<<< orphan*/  mcam_reg_set_bit (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cafe_smbus_enable_irq(struct cafe_camera *cam)
{
	unsigned long flags;

	spin_lock_irqsave(&cam->mcam.dev_lock, flags);
	mcam_reg_set_bit(&cam->mcam, REG_IRQMASK, TWSIIRQS);
	spin_unlock_irqrestore(&cam->mcam.dev_lock, flags);
}