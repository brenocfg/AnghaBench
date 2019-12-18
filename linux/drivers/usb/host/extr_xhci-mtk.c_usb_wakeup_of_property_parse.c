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
struct xhci_hcd_mtk {int /*<<< orphan*/  uwk; int /*<<< orphan*/  uwk_vers; int /*<<< orphan*/  uwk_reg_base; int /*<<< orphan*/  dev; int /*<<< orphan*/  uwk_en; } ;
struct of_phandle_args {int /*<<< orphan*/  np; int /*<<< orphan*/ * args; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int PTR_ERR_OR_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int of_parse_phandle_with_fixed_args (struct device_node*,char*,int,int /*<<< orphan*/ ,struct of_phandle_args*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_wakeup_of_property_parse(struct xhci_hcd_mtk *mtk,
				struct device_node *dn)
{
	struct of_phandle_args args;
	int ret;

	/* Wakeup function is optional */
	mtk->uwk_en = of_property_read_bool(dn, "wakeup-source");
	if (!mtk->uwk_en)
		return 0;

	ret = of_parse_phandle_with_fixed_args(dn,
				"mediatek,syscon-wakeup", 2, 0, &args);
	if (ret)
		return ret;

	mtk->uwk_reg_base = args.args[0];
	mtk->uwk_vers = args.args[1];
	mtk->uwk = syscon_node_to_regmap(args.np);
	of_node_put(args.np);
	dev_info(mtk->dev, "uwk - reg:0x%x, version:%d\n",
			mtk->uwk_reg_base, mtk->uwk_vers);

	return PTR_ERR_OR_ZERO(mtk->uwk);

}