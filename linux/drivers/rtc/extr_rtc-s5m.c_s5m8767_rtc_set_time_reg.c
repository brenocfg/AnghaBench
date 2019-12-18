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
struct s5m_rtc_info {int /*<<< orphan*/  dev; TYPE_1__* regs; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int write_time_udr_mask; int /*<<< orphan*/  udr_update; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int s5m8767_wait_for_udr_update (struct s5m_rtc_info*) ; 

__attribute__((used)) static int s5m8767_rtc_set_time_reg(struct s5m_rtc_info *info)
{
	int ret;
	unsigned int data;

	ret = regmap_read(info->regmap, info->regs->udr_update, &data);
	if (ret < 0) {
		dev_err(info->dev, "failed to read update reg(%d)\n", ret);
		return ret;
	}

	data |= info->regs->write_time_udr_mask;

	ret = regmap_write(info->regmap, info->regs->udr_update, data);
	if (ret < 0) {
		dev_err(info->dev, "failed to write update reg(%d)\n", ret);
		return ret;
	}

	ret = s5m8767_wait_for_udr_update(info);

	return ret;
}