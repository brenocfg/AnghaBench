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
struct adf_cfg_device_data {int /*<<< orphan*/  lock; } ;
struct adf_accel_dev {struct adf_cfg_device_data* cfg; } ;

/* Variables and functions */
 int adf_cfg_key_val_get (struct adf_accel_dev*,char const*,char const*,char*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int adf_cfg_get_param_value(struct adf_accel_dev *accel_dev,
			    const char *section, const char *name,
			    char *value)
{
	struct adf_cfg_device_data *cfg = accel_dev->cfg;
	int ret;

	down_read(&cfg->lock);
	ret = adf_cfg_key_val_get(accel_dev, section, name, value);
	up_read(&cfg->lock);
	return ret;
}