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
struct mtk_mdp_comp {scalar_t__ larb_dev; int /*<<< orphan*/ * clk; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_smi_larb_put (scalar_t__) ; 

void mtk_mdp_comp_clock_off(struct device *dev, struct mtk_mdp_comp *comp)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(comp->clk); i++) {
		if (IS_ERR(comp->clk[i]))
			continue;
		clk_disable_unprepare(comp->clk[i]);
	}

	if (comp->larb_dev)
		mtk_smi_larb_put(comp->larb_dev);
}