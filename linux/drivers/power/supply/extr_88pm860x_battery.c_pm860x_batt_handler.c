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
struct pm860x_battery_info {int present; int /*<<< orphan*/  lock; int /*<<< orphan*/  temp_type; int /*<<< orphan*/  i2c; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PM8607_STATUS_2 ; 
 int /*<<< orphan*/  PM860X_TEMP_TBAT ; 
 int /*<<< orphan*/  PM860X_TEMP_TINT ; 
 int STATUS2_BAT ; 
 int /*<<< orphan*/  ccnt_data ; 
 int /*<<< orphan*/  clear_ccnt (struct pm860x_battery_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pm860x_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pm860x_batt_handler(int irq, void *data)
{
	struct pm860x_battery_info *info = data;
	int ret;

	mutex_lock(&info->lock);
	ret = pm860x_reg_read(info->i2c, PM8607_STATUS_2);
	if (ret & STATUS2_BAT) {
		info->present = 1;
		info->temp_type = PM860X_TEMP_TBAT;
	} else {
		info->present = 0;
		info->temp_type = PM860X_TEMP_TINT;
	}
	mutex_unlock(&info->lock);
	/* clear ccnt since battery is attached or dettached */
	clear_ccnt(info, &ccnt_data);
	return IRQ_HANDLED;
}