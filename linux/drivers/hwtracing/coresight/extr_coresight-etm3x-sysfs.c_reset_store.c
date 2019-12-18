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
struct etm_config {int /*<<< orphan*/ * addr_type; int /*<<< orphan*/  trigger_event; int /*<<< orphan*/  mode; } ;
struct etm_drvdata {int nr_addr_cmp; int /*<<< orphan*/  spinlock; struct etm_config config; } ;
struct device_attribute {int dummy; } ;
struct device {int /*<<< orphan*/  parent; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETM_ADDR_TYPE_NONE ; 
 int /*<<< orphan*/  ETM_DEFAULT_EVENT_VAL ; 
 int /*<<< orphan*/  ETM_MODE_EXCLUDE ; 
 struct etm_drvdata* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  etm_set_default (struct etm_config*) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  memset (struct etm_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t reset_store(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t size)
{
	int i, ret;
	unsigned long val;
	struct etm_drvdata *drvdata = dev_get_drvdata(dev->parent);
	struct etm_config *config = &drvdata->config;

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	if (val) {
		spin_lock(&drvdata->spinlock);
		memset(config, 0, sizeof(struct etm_config));
		config->mode = ETM_MODE_EXCLUDE;
		config->trigger_event = ETM_DEFAULT_EVENT_VAL;
		for (i = 0; i < drvdata->nr_addr_cmp; i++) {
			config->addr_type[i] = ETM_ADDR_TYPE_NONE;
		}

		etm_set_default(config);
		spin_unlock(&drvdata->spinlock);
	}

	return size;
}