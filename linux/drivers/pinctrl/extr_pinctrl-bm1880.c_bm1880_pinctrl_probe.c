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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct bm1880_pinctrl {int /*<<< orphan*/  pctrldev; int /*<<< orphan*/  pinconf; void* nfuncs; void* funcs; void* ngroups; void* groups; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm1880_desc ; 
 void* bm1880_pctrl_groups ; 
 int /*<<< orphan*/  bm1880_pinconf ; 
 void* bm1880_pmux_functions ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct bm1880_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct bm1880_pinctrl*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bm1880_pinctrl*) ; 

__attribute__((used)) static int bm1880_pinctrl_probe(struct platform_device *pdev)

{
	struct resource *res;
	struct bm1880_pinctrl *pctrl;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pctrl->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pctrl->base))
		return PTR_ERR(pctrl->base);

	pctrl->groups = bm1880_pctrl_groups;
	pctrl->ngroups = ARRAY_SIZE(bm1880_pctrl_groups);
	pctrl->funcs = bm1880_pmux_functions;
	pctrl->nfuncs = ARRAY_SIZE(bm1880_pmux_functions);
	pctrl->pinconf = bm1880_pinconf;

	pctrl->pctrldev = devm_pinctrl_register(&pdev->dev, &bm1880_desc,
						pctrl);
	if (IS_ERR(pctrl->pctrldev))
		return PTR_ERR(pctrl->pctrldev);

	platform_set_drvdata(pdev, pctrl);

	dev_info(&pdev->dev, "BM1880 pinctrl driver initialized\n");

	return 0;
}