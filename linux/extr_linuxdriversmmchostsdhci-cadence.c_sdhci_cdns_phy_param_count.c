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
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  property; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,int /*<<< orphan*/ ) ; 
 TYPE_1__* sdhci_cdns_phy_cfgs ; 

__attribute__((used)) static unsigned int sdhci_cdns_phy_param_count(struct device_node *np)
{
	unsigned int count = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(sdhci_cdns_phy_cfgs); i++)
		if (of_property_read_bool(np, sdhci_cdns_phy_cfgs[i].property))
			count++;

	return count;
}