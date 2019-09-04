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
struct mtk_mdp_comp {int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/ * clk; scalar_t__ larb_dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int mtk_smi_larb_get (scalar_t__) ; 

void mtk_mdp_comp_clock_on(struct device *dev, struct mtk_mdp_comp *comp)
{
	int i, err;

	if (comp->larb_dev) {
		err = mtk_smi_larb_get(comp->larb_dev);
		if (err)
			dev_err(dev,
				"failed to get larb, err %d. type:%d id:%d\n",
				err, comp->type, comp->id);
	}

	for (i = 0; i < ARRAY_SIZE(comp->clk); i++) {
		if (IS_ERR(comp->clk[i]))
			continue;
		err = clk_prepare_enable(comp->clk[i]);
		if (err)
			dev_err(dev,
			"failed to enable clock, err %d. type:%d id:%d i:%d\n",
				err, comp->type, comp->id, i);
	}
}