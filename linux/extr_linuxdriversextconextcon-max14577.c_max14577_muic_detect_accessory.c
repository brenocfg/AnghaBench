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
struct max14577_muic_info {int /*<<< orphan*/  mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  status; TYPE_1__* max14577; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX14577_CABLE_GROUP_ADC ; 
 int /*<<< orphan*/  MAX14577_CABLE_GROUP_CHG ; 
 int MAX14577_CHARGER_TYPE_NONE ; 
 int MAX14577_MUIC_ADC_OPEN ; 
 int /*<<< orphan*/  MAX14577_MUIC_REG_STATUS1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int max14577_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int max14577_muic_adc_handler (struct max14577_muic_info*) ; 
 int max14577_muic_chg_handler (struct max14577_muic_info*) ; 
 int max14577_muic_get_cable_type (struct max14577_muic_info*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max14577_muic_detect_accessory(struct max14577_muic_info *info)
{
	int ret = 0;
	int adc;
	int chg_type;
	bool attached;

	mutex_lock(&info->mutex);

	/* Read STATUSx register to detect accessory */
	ret = max14577_bulk_read(info->max14577->regmap,
			MAX14577_MUIC_REG_STATUS1, info->status, 2);
	if (ret) {
		dev_err(info->dev, "failed to read MUIC register\n");
		mutex_unlock(&info->mutex);
		return ret;
	}

	adc = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_ADC,
					&attached);
	if (attached && adc != MAX14577_MUIC_ADC_OPEN) {
		ret = max14577_muic_adc_handler(info);
		if (ret < 0) {
			dev_err(info->dev, "Cannot detect accessory\n");
			mutex_unlock(&info->mutex);
			return ret;
		}
	}

	chg_type = max14577_muic_get_cable_type(info, MAX14577_CABLE_GROUP_CHG,
					&attached);
	if (attached && chg_type != MAX14577_CHARGER_TYPE_NONE) {
		ret = max14577_muic_chg_handler(info);
		if (ret < 0) {
			dev_err(info->dev, "Cannot detect charger accessory\n");
			mutex_unlock(&info->mutex);
			return ret;
		}
	}

	mutex_unlock(&info->mutex);

	return 0;
}