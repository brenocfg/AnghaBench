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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_cc_resources (struct platform_device*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 

__attribute__((used)) static int ccree_remove(struct platform_device *plat_dev)
{
	struct device *dev = &plat_dev->dev;

	dev_dbg(dev, "Releasing ccree resources...\n");

	cleanup_cc_resources(plat_dev);

	dev_info(dev, "ARM ccree device terminated\n");

	return 0;
}