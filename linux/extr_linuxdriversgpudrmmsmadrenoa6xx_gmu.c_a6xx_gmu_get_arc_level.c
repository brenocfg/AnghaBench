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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct dev_pm_opp {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dev_pm_opp*) ; 
 struct dev_pm_opp* dev_pm_opp_find_freq_exact (struct device*,unsigned long,int) ; 
 struct device_node* dev_pm_opp_get_of_node (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  dev_pm_opp_put (struct dev_pm_opp*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 a6xx_gmu_get_arc_level(struct device *dev, unsigned long freq)
{
	struct dev_pm_opp *opp;
	struct device_node *np;
	u32 val = 0;

	if (!freq)
		return 0;

	opp  = dev_pm_opp_find_freq_exact(dev, freq, true);
	if (IS_ERR(opp))
		return 0;

	np = dev_pm_opp_get_of_node(opp);

	if (np) {
		of_property_read_u32(np, "opp-level", &val);
		of_node_put(np);
	}

	dev_pm_opp_put(opp);

	return val;
}