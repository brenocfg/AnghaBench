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
struct rt9455_info {int /*<<< orphan*/  batt_presence_work; int /*<<< orphan*/  max_charging_time_work; int /*<<< orphan*/ * regmap_fields; int /*<<< orphan*/  regmap; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 size_t F_BATAB ; 
 size_t F_BATABM ; 
 size_t F_CHRCHGIM ; 
 size_t F_CHTERMIM ; 
 size_t F_TSDI ; 
 size_t F_VINOVPI ; 
 unsigned int GET_MASK (size_t) ; 
 int HZ ; 
 int RT9455_BATT_PRESENCE_DELAY ; 
 int /*<<< orphan*/  RT9455_REG_IRQ1 ; 
 int /*<<< orphan*/  RT9455_REG_MASK1 ; 
 int /*<<< orphan*/  RT9455_REG_MASK2 ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_field_write (int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static int rt9455_irq_handler_check_irq1_register(struct rt9455_info *info,
						  bool *_is_battery_absent,
						  bool *_alert_userspace)
{
	unsigned int irq1, mask1, mask2;
	struct device *dev = &info->client->dev;
	bool is_battery_absent = false;
	bool alert_userspace = false;
	int ret;

	ret = regmap_read(info->regmap, RT9455_REG_IRQ1, &irq1);
	if (ret) {
		dev_err(dev, "Failed to read IRQ1 register\n");
		return ret;
	}

	ret = regmap_read(info->regmap, RT9455_REG_MASK1, &mask1);
	if (ret) {
		dev_err(dev, "Failed to read MASK1 register\n");
		return ret;
	}

	if (irq1 & GET_MASK(F_TSDI)) {
		dev_err(dev, "Thermal shutdown fault occurred\n");
		alert_userspace = true;
	}

	if (irq1 & GET_MASK(F_VINOVPI)) {
		dev_err(dev, "Overvoltage input occurred\n");
		alert_userspace = true;
	}

	if (irq1 & GET_MASK(F_BATAB)) {
		dev_err(dev, "Battery absence occurred\n");
		is_battery_absent = true;
		alert_userspace = true;

		if ((mask1 & GET_MASK(F_BATABM)) == 0) {
			ret = regmap_field_write(info->regmap_fields[F_BATABM],
						 0x01);
			if (ret) {
				dev_err(dev, "Failed to mask BATAB interrupt\n");
				return ret;
			}
		}

		ret = regmap_read(info->regmap, RT9455_REG_MASK2, &mask2);
		if (ret) {
			dev_err(dev, "Failed to read MASK2 register\n");
			return ret;
		}

		if (mask2 & GET_MASK(F_CHTERMIM)) {
			ret = regmap_field_write(
				info->regmap_fields[F_CHTERMIM], 0x00);
			if (ret) {
				dev_err(dev, "Failed to unmask CHTERMI interrupt\n");
				return ret;
			}
		}

		if (mask2 & GET_MASK(F_CHRCHGIM)) {
			ret = regmap_field_write(
				info->regmap_fields[F_CHRCHGIM], 0x00);
			if (ret) {
				dev_err(dev, "Failed to unmask CHRCHGI interrupt\n");
				return ret;
			}
		}

		/*
		 * When the battery is absent, max_charging_time_work is
		 * cancelled, since no charging is done.
		 */
		cancel_delayed_work_sync(&info->max_charging_time_work);
		/*
		 * Since no interrupt is triggered when the battery is
		 * reconnected, max_charging_time_work is not rescheduled.
		 * Therefore, batt_presence_work is scheduled to check whether
		 * the battery is still absent or not.
		 */
		queue_delayed_work(system_power_efficient_wq,
				   &info->batt_presence_work,
				   RT9455_BATT_PRESENCE_DELAY * HZ);
	}

	*_is_battery_absent = is_battery_absent;

	if (alert_userspace)
		*_alert_userspace = alert_userspace;

	return 0;
}