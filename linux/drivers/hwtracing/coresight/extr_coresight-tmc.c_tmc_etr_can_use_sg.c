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
struct device {int /*<<< orphan*/  fwnode; } ;

/* Variables and functions */
 int fwnode_property_present (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline bool tmc_etr_can_use_sg(struct device *dev)
{
	return fwnode_property_present(dev->fwnode, "arm,scatter-gather");
}