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
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct da9150_fg_pdata {int /*<<< orphan*/  crit_soc_lvl; int /*<<< orphan*/  warn_soc_lvl; int /*<<< orphan*/  update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct da9150_fg_pdata* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_property_read_u8 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct da9150_fg_pdata *da9150_fg_dt_pdata(struct device *dev)
{
	struct device_node *fg_node = dev->of_node;
	struct da9150_fg_pdata *pdata;

	pdata = devm_kzalloc(dev, sizeof(struct da9150_fg_pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	of_property_read_u32(fg_node, "dlg,update-interval",
			     &pdata->update_interval);
	of_property_read_u8(fg_node, "dlg,warn-soc-level",
			    &pdata->warn_soc_lvl);
	of_property_read_u8(fg_node, "dlg,crit-soc-level",
			    &pdata->crit_soc_lvl);

	return pdata;
}