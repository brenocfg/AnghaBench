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
typedef  int u32 ;
struct ltc294x_info {int id; int /*<<< orphan*/  client; } ;

/* Variables and functions */
#define  LTC2943_ID 129 
#define  LTC2944_ID 128 
 int /*<<< orphan*/  LTC294X_REG_VOLTAGE_MSB ; 
 int ltc294x_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int ltc294x_get_voltage(const struct ltc294x_info *info, int *val)
{
	int ret;
	u8 datar[2];
	u32 value;

	ret = ltc294x_read_regs(info->client,
		LTC294X_REG_VOLTAGE_MSB, &datar[0], 2);
	value = (datar[0] << 8) | datar[1];
	switch (info->id) {
	case LTC2943_ID:
		value *= 23600 * 2;
		value /= 0xFFFF;
		value *= 1000 / 2;
		break;
	case LTC2944_ID:
		value *= 70800 / 5*4;
		value /= 0xFFFF;
		value *= 1000 * 5/4;
		break;
	default:
		value *= 6000 * 10;
		value /= 0xFFFF;
		value *= 1000 / 10;
		break;
	}
	*val = value;
	return ret;
}