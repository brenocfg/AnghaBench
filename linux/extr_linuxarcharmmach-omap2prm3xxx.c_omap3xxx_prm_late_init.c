#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_3__ {int irq; int /*<<< orphan*/  reconfigure_io_chain; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int PRM_HAS_IO_WAKEUP ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3430_pre_es3_1_reconfigure_io_chain ; 
 scalar_t__ omap3_has_io_chain_ctrl () ; 
 TYPE_1__ omap3_prcm_irq_setup ; 
 int /*<<< orphan*/  omap3_prm_dt_match_table ; 
 int /*<<< orphan*/  omap3_prm_reconfigure_io_chain ; 
 int /*<<< orphan*/  omap3xxx_prm_enable_io_wakeup () ; 
 int omap_prcm_register_chain_handler (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int prm_features ; 

__attribute__((used)) static int omap3xxx_prm_late_init(void)
{
	struct device_node *np;
	int irq_num;

	if (!(prm_features & PRM_HAS_IO_WAKEUP))
		return 0;

	if (omap3_has_io_chain_ctrl())
		omap3_prcm_irq_setup.reconfigure_io_chain =
			omap3_prm_reconfigure_io_chain;
	else
		omap3_prcm_irq_setup.reconfigure_io_chain =
			omap3430_pre_es3_1_reconfigure_io_chain;

	np = of_find_matching_node(NULL, omap3_prm_dt_match_table);
	if (!np) {
		pr_err("PRM: no device tree node for interrupt?\n");

		return -ENODEV;
	}

	irq_num = of_irq_get(np, 0);
	if (irq_num == -EPROBE_DEFER)
		return irq_num;

	omap3_prcm_irq_setup.irq = irq_num;

	omap3xxx_prm_enable_io_wakeup();

	return omap_prcm_register_chain_handler(&omap3_prcm_irq_setup);
}