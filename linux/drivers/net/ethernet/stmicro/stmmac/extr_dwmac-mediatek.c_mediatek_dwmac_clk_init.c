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
struct mediatek_dwmac_variant {int num_clks; int /*<<< orphan*/ * clk_list; } ;
struct mediatek_dwmac_plat_data {TYPE_1__* clks; int /*<<< orphan*/  dev; struct mediatek_dwmac_variant* variant; } ;
struct TYPE_3__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int devm_clk_bulk_get (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 TYPE_1__* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mediatek_dwmac_clk_init(struct mediatek_dwmac_plat_data *plat)
{
	const struct mediatek_dwmac_variant *variant = plat->variant;
	int i, num = variant->num_clks;

	plat->clks = devm_kcalloc(plat->dev, num, sizeof(*plat->clks), GFP_KERNEL);
	if (!plat->clks)
		return -ENOMEM;

	for (i = 0; i < num; i++)
		plat->clks[i].id = variant->clk_list[i];

	return devm_clk_bulk_get(plat->dev, num, plat->clks);
}