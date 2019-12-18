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

/* Variables and functions */
 int /*<<< orphan*/  a3xx_ops ; 
 int /*<<< orphan*/  adreno_device_register_headless () ; 
 int component_add (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int adreno_probe(struct platform_device *pdev)
{

	int ret;

	ret = component_add(&pdev->dev, &a3xx_ops);
	if (ret)
		return ret;

	if (of_device_is_compatible(pdev->dev.of_node, "amd,imageon"))
		adreno_device_register_headless();

	return 0;
}