#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ val; } ;
struct TYPE_5__ {TYPE_1__ init; } ;

/* Variables and functions */
 TYPE_3__* adapter_parm ; 
 int /*<<< orphan*/ * ara ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  line_set (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  parport_adapter ; 
 TYPE_1__ parport_ctrl_irq ; 
 size_t type ; 

__attribute__((used)) static int i2c_parport_remove(struct platform_device *pdev)
{
	if (ara) {
		line_set(0, &parport_ctrl_irq);
		i2c_unregister_device(ara);
		ara = NULL;
	}
	i2c_del_adapter(&parport_adapter);

	/* Un-init if needed (power off...) */
	if (adapter_parm[type].init.val)
		line_set(0, &adapter_parm[type].init);

	return 0;
}