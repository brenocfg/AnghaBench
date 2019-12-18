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
struct resource {int dummy; } ;
struct TYPE_3__ {void* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int /*<<< orphan*/  high_mpp_base ; 
 int /*<<< orphan*/  mpp_base ; 
 int mvebu_pinctrl_probe (struct platform_device*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  orion_pinctrl_of_match ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int orion_pinctrl_probe(struct platform_device *pdev)
{
	const struct of_device_id *match =
		of_match_device(orion_pinctrl_of_match, &pdev->dev);
	struct resource *res;

	pdev->dev.platform_data = (void*)match->data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	mpp_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(mpp_base))
		return PTR_ERR(mpp_base);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	high_mpp_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(high_mpp_base))
		return PTR_ERR(high_mpp_base);

	return mvebu_pinctrl_probe(pdev);
}