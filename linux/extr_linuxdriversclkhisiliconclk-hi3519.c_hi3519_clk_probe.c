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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct hi3519_crg_data {int /*<<< orphan*/  clk_data; int /*<<< orphan*/  rstc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct hi3519_crg_data* devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3519_clk_register (struct platform_device*) ; 
 int /*<<< orphan*/  hisi_reset_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_reset_init (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct hi3519_crg_data*) ; 

__attribute__((used)) static int hi3519_clk_probe(struct platform_device *pdev)
{
	struct hi3519_crg_data *crg;

	crg = devm_kmalloc(&pdev->dev, sizeof(*crg), GFP_KERNEL);
	if (!crg)
		return -ENOMEM;

	crg->rstc = hisi_reset_init(pdev);
	if (!crg->rstc)
		return -ENOMEM;

	crg->clk_data = hi3519_clk_register(pdev);
	if (IS_ERR(crg->clk_data)) {
		hisi_reset_exit(crg->rstc);
		return PTR_ERR(crg->clk_data);
	}

	platform_set_drvdata(pdev, crg);
	return 0;
}