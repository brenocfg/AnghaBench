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
struct rpisense {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*,...) ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (char const*,int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rpisense*) ; 

__attribute__((used)) static void rpisense_client_dev_register(struct rpisense *rpisense,
					 const char *name,
					 struct platform_device **pdev)
{
	int ret;

	*pdev = platform_device_alloc(name, -1);
	if (*pdev == NULL) {
		dev_err(rpisense->dev, "Failed to allocate %s\n", name);
		return;
	}

	(*pdev)->dev.parent = rpisense->dev;
	platform_set_drvdata(*pdev, rpisense);
	ret = platform_device_add(*pdev);
	if (ret != 0) {
		dev_err(rpisense->dev, "Failed to register %s: %d\n",
			name, ret);
		platform_device_put(*pdev);
		*pdev = NULL;
	}
}