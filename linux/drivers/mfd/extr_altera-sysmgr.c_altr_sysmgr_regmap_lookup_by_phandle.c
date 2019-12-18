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
struct regmap {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;
struct altr_sysmgr {struct regmap* regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct regmap* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__ altr_sysmgr_driver ; 
 struct altr_sysmgr* dev_get_drvdata (struct device*) ; 
 struct device* driver_find_device_by_of_node (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char const*,int /*<<< orphan*/ ) ; 

struct regmap *altr_sysmgr_regmap_lookup_by_phandle(struct device_node *np,
						    const char *property)
{
	struct device *dev;
	struct altr_sysmgr *sysmgr;
	struct device_node *sysmgr_np;

	if (property)
		sysmgr_np = of_parse_phandle(np, property, 0);
	else
		sysmgr_np = np;

	if (!sysmgr_np)
		return ERR_PTR(-ENODEV);

	dev = driver_find_device_by_of_node(&altr_sysmgr_driver.driver,
					    (void *)sysmgr_np);
	of_node_put(sysmgr_np);
	if (!dev)
		return ERR_PTR(-EPROBE_DEFER);

	sysmgr = dev_get_drvdata(dev);

	return sysmgr->regmap;
}