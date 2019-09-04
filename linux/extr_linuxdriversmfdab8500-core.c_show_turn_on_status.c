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
typedef  int u8 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ab8500 {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_SYS_CTRL1_BLOCK ; 
 int /*<<< orphan*/  AB8500_TURN_ON_STATUS ; 
 struct ab8500* dev_get_drvdata (struct device*) ; 
 int get_register_interruptible (struct ab8500*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_ab9540 (struct ab8500*) ; 
 int /*<<< orphan*/  on_stat_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,int) ; 
 int turn_on_stat_mask ; 
 int turn_on_stat_set ; 

__attribute__((used)) static ssize_t show_turn_on_status(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	int ret;
	u8 value;
	struct ab8500 *ab8500;

	ab8500 = dev_get_drvdata(dev);
	ret = get_register_interruptible(ab8500, AB8500_SYS_CTRL1_BLOCK,
		AB8500_TURN_ON_STATUS, &value);
	if (ret < 0)
		return ret;

	/*
	 * In L9540, turn_on_status register is not updated correctly if
	 * the device is rebooted with AC/USB charger connected. Due to
	 * this, the device boots android instead of entering into charge
	 * only mode. Read the AC/USB status register to detect the charger
	 * presence and update the turn on status manually.
	 */
	if (is_ab9540(ab8500)) {
		spin_lock(&on_stat_lock);
		value = (value & turn_on_stat_mask) | turn_on_stat_set;
		spin_unlock(&on_stat_lock);
	}

	return sprintf(buf, "%#x\n", value);
}