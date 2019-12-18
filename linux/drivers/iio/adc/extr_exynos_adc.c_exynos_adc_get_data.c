#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct exynos_adc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exynos_adc_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct exynos_adc_data *exynos_adc_get_data(struct platform_device *pdev)
{
	const struct of_device_id *match;

	match = of_match_node(exynos_adc_match, pdev->dev.of_node);
	return (struct exynos_adc_data *)match->data;
}