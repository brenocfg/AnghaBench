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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  LTC2990_CURR1 137 
#define  LTC2990_CURR2 136 
#define  LTC2990_IN0 135 
#define  LTC2990_IN1 134 
#define  LTC2990_IN2 133 
#define  LTC2990_IN3 132 
#define  LTC2990_IN4 131 
#define  LTC2990_TEMP1 130 
#define  LTC2990_TEMP2 129 
#define  LTC2990_TEMP3 128 
 int /*<<< orphan*/  LTC2990_TINT_MSB ; 
 int /*<<< orphan*/  LTC2990_V1_MSB ; 
 int /*<<< orphan*/  LTC2990_V2_MSB ; 
 int /*<<< orphan*/  LTC2990_V3_MSB ; 
 int /*<<< orphan*/  LTC2990_V4_MSB ; 
 int /*<<< orphan*/  LTC2990_VCC_MSB ; 
 int i2c_smbus_read_word_swapped (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int sign_extend32 (int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ltc2990_get_value(struct i2c_client *i2c, int index, int *result)
{
	int val;
	u8 reg;

	switch (index) {
	case LTC2990_IN0:
		reg = LTC2990_VCC_MSB;
		break;
	case LTC2990_IN1:
	case LTC2990_CURR1:
	case LTC2990_TEMP2:
		reg = LTC2990_V1_MSB;
		break;
	case LTC2990_IN2:
		reg = LTC2990_V2_MSB;
		break;
	case LTC2990_IN3:
	case LTC2990_CURR2:
	case LTC2990_TEMP3:
		reg = LTC2990_V3_MSB;
		break;
	case LTC2990_IN4:
		reg = LTC2990_V4_MSB;
		break;
	case LTC2990_TEMP1:
		reg = LTC2990_TINT_MSB;
		break;
	default:
		return -EINVAL;
	}

	val = i2c_smbus_read_word_swapped(i2c, reg);
	if (unlikely(val < 0))
		return val;

	switch (index) {
	case LTC2990_TEMP1:
	case LTC2990_TEMP2:
	case LTC2990_TEMP3:
		/* temp, 0.0625 degrees/LSB */
		*result = sign_extend32(val, 12) * 1000 / 16;
		break;
	case LTC2990_CURR1:
	case LTC2990_CURR2:
		 /* Vx-Vy, 19.42uV/LSB */
		*result = sign_extend32(val, 14) * 1942 / 100;
		break;
	case LTC2990_IN0:
		/* Vcc, 305.18uV/LSB, 2.5V offset */
		*result = sign_extend32(val, 14) * 30518 / (100 * 1000) + 2500;
		break;
	case LTC2990_IN1:
	case LTC2990_IN2:
	case LTC2990_IN3:
	case LTC2990_IN4:
		/* Vx, 305.18uV/LSB */
		*result = sign_extend32(val, 14) * 30518 / (100 * 1000);
		break;
	default:
		return -EINVAL; /* won't happen, keep compiler happy */
	}

	return 0;
}