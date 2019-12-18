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

/* Variables and functions */
 scalar_t__ of_device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sun5i_pinctrl_data ; 
 int sunxi_pinctrl_init_with_variant (struct platform_device*,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int sun5i_pinctrl_probe(struct platform_device *pdev)
{
	unsigned long variant = (unsigned long)of_device_get_match_data(&pdev->dev);

	return sunxi_pinctrl_init_with_variant(pdev, &sun5i_pinctrl_data,
					       variant);
}