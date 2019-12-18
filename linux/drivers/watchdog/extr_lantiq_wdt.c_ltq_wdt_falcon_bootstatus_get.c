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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct regmap*) ; 
 int /*<<< orphan*/  LTQ_FALCON_SYS1_CPU0RS ; 
 int LTQ_FALCON_SYS1_CPU0RS_MASK ; 
 int LTQ_FALCON_SYS1_CPU0RS_WDT ; 
 int PTR_ERR (struct regmap*) ; 
 int WDIOF_CARDRESET ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct regmap* syscon_regmap_lookup_by_phandle (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int ltq_wdt_falcon_bootstatus_get(struct device *dev)
{
	struct regmap *rcu_regmap;
	u32 val;
	int err;

	rcu_regmap = syscon_regmap_lookup_by_phandle(dev->of_node,
						     "lantiq,rcu");
	if (IS_ERR(rcu_regmap))
		return PTR_ERR(rcu_regmap);

	err = regmap_read(rcu_regmap, LTQ_FALCON_SYS1_CPU0RS, &val);
	if (err)
		return err;

	if ((val & LTQ_FALCON_SYS1_CPU0RS_MASK) == LTQ_FALCON_SYS1_CPU0RS_WDT)
		return WDIOF_CARDRESET;

	return 0;
}