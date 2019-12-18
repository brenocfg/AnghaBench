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
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,unsigned int) ; 
 int resource_size (struct resource*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static size_t tegra_pinctrl_get_bank_size(struct device *dev,
					  unsigned int bank_id)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *res;

	res = platform_get_resource(pdev, IORESOURCE_MEM, bank_id);

	return resource_size(res) / 4;
}