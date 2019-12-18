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
struct saa7146_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  msp430_irq_tasklet; } ;
struct TYPE_3__ {struct saa7146_dev* dev; } ;
struct budget_ci {TYPE_2__ ir; TYPE_1__ budget; } ;

/* Variables and functions */
 int /*<<< orphan*/  MASK_06 ; 
 int /*<<< orphan*/  SAA7146_GPIO_INPUT ; 
 int /*<<< orphan*/  SAA7146_IER_DISABLE (struct saa7146_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  saa7146_setgpio (struct saa7146_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void msp430_ir_deinit(struct budget_ci *budget_ci)
{
	struct saa7146_dev *saa = budget_ci->budget.dev;

	SAA7146_IER_DISABLE(saa, MASK_06);
	saa7146_setgpio(saa, 3, SAA7146_GPIO_INPUT);
	tasklet_kill(&budget_ci->ir.msp430_irq_tasklet);

	rc_unregister_device(budget_ci->ir.dev);
}