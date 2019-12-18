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
struct mtk_ecc {int /*<<< orphan*/  clk; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct mtk_ecc* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_ecc_hw_init (struct mtk_ecc*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct mtk_ecc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mtk_ecc *mtk_ecc_get(struct device_node *np)
{
	struct platform_device *pdev;
	struct mtk_ecc *ecc;

	pdev = of_find_device_by_node(np);
	if (!pdev)
		return ERR_PTR(-EPROBE_DEFER);

	ecc = platform_get_drvdata(pdev);
	if (!ecc) {
		put_device(&pdev->dev);
		return ERR_PTR(-EPROBE_DEFER);
	}

	clk_prepare_enable(ecc->clk);
	mtk_ecc_hw_init(ecc);

	return ecc;
}