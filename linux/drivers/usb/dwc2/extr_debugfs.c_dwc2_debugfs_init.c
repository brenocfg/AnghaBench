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
struct dwc2_hsotg {struct dentry* debug_root; TYPE_1__* regset; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; } ;
struct dentry {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/  nregs; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct dentry* debugfs_create_dir (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_file (char*,int,struct dentry*,struct dwc2_hsotg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_regset32 (char*,int,struct dentry*,TYPE_1__*) ; 
 int /*<<< orphan*/  debugfs_remove_recursive (struct dentry*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 TYPE_1__* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dr_mode_fops ; 
 int /*<<< orphan*/  dwc2_hsotg_create_debug (struct dwc2_hsotg*) ; 
 int /*<<< orphan*/  dwc2_regs ; 
 int /*<<< orphan*/  hw_params_fops ; 
 int /*<<< orphan*/  params_fops ; 

int dwc2_debugfs_init(struct dwc2_hsotg *hsotg)
{
	int			ret;
	struct dentry		*root;

	root = debugfs_create_dir(dev_name(hsotg->dev), NULL);
	hsotg->debug_root = root;

	debugfs_create_file("params", 0444, root, hsotg, &params_fops);
	debugfs_create_file("hw_params", 0444, root, hsotg, &hw_params_fops);
	debugfs_create_file("dr_mode", 0444, root, hsotg, &dr_mode_fops);

	/* Add gadget debugfs nodes */
	dwc2_hsotg_create_debug(hsotg);

	hsotg->regset = devm_kzalloc(hsotg->dev, sizeof(*hsotg->regset),
								GFP_KERNEL);
	if (!hsotg->regset) {
		ret = -ENOMEM;
		goto err;
	}

	hsotg->regset->regs = dwc2_regs;
	hsotg->regset->nregs = ARRAY_SIZE(dwc2_regs);
	hsotg->regset->base = hsotg->regs;

	debugfs_create_regset32("regdump", 0444, root, hsotg->regset);

	return 0;
err:
	debugfs_remove_recursive(hsotg->debug_root);
	return ret;
}