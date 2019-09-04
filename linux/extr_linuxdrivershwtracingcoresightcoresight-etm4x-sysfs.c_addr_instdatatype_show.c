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
typedef  size_t u8 ;
struct etmv4_config {size_t addr_idx; int /*<<< orphan*/ * addr_acc; } ;
struct etmv4_drvdata {int /*<<< orphan*/  spinlock; struct etmv4_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 size_t BMVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 size_t ETM_DATA_LOAD_ADDR ; 
 size_t ETM_DATA_STORE_ADDR ; 
 size_t ETM_INSTR_ADDR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct etmv4_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scnprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t addr_instdatatype_show(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	ssize_t len;
	u8 val, idx;
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etmv4_config *config = &drvdata->config;

	spin_lock(&drvdata->spinlock);
	idx = config->addr_idx;
	val = BMVAL(config->addr_acc[idx], 0, 1);
	len = scnprintf(buf, PAGE_SIZE, "%s\n",
			val == ETM_INSTR_ADDR ? "instr" :
			(val == ETM_DATA_LOAD_ADDR ? "data_load" :
			(val == ETM_DATA_STORE_ADDR ? "data_store" :
			"data_load_store")));
	spin_unlock(&drvdata->spinlock);
	return len;
}