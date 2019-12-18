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
struct s5m_rtc_info {int device_type; TYPE_1__* s5m87xx; int /*<<< orphan*/  regmap; } ;
struct rtc_wkalrm {int pending; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap_pmic; } ;

/* Variables and functions */
 int EINVAL ; 
#define  S2MPS13X 132 
#define  S2MPS14X 131 
 int /*<<< orphan*/  S2MPS14_REG_ST2 ; 
#define  S2MPS15X 130 
 unsigned int S2MPS_ALARM0_STATUS ; 
#define  S5M8763X 129 
#define  S5M8767X 128 
 unsigned int S5M_ALARM0_STATUS ; 
 int /*<<< orphan*/  S5M_RTC_STATUS ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int s5m_check_peding_alarm_interrupt(struct s5m_rtc_info *info,
		struct rtc_wkalrm *alarm)
{
	int ret;
	unsigned int val;

	switch (info->device_type) {
	case S5M8767X:
	case S5M8763X:
		ret = regmap_read(info->regmap, S5M_RTC_STATUS, &val);
		val &= S5M_ALARM0_STATUS;
		break;
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		ret = regmap_read(info->s5m87xx->regmap_pmic, S2MPS14_REG_ST2,
				&val);
		val &= S2MPS_ALARM0_STATUS;
		break;
	default:
		return -EINVAL;
	}
	if (ret < 0)
		return ret;

	if (val)
		alarm->pending = 1;
	else
		alarm->pending = 0;

	return 0;
}