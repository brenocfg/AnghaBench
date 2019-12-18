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
struct ltc4245_data {int* vregs; } ;
struct device {int dummy; } ;

/* Variables and functions */
#define  LTC4245_12VIN 136 
#define  LTC4245_12VOUT 135 
#define  LTC4245_3VIN 134 
#define  LTC4245_3VOUT 133 
#define  LTC4245_5VIN 132 
#define  LTC4245_5VOUT 131 
#define  LTC4245_GPIOADC 130 
#define  LTC4245_VEEIN 129 
#define  LTC4245_VEEOUT 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ltc4245_data* ltc4245_update_device (struct device*) ; 

__attribute__((used)) static int ltc4245_get_voltage(struct device *dev, u8 reg)
{
	struct ltc4245_data *data = ltc4245_update_device(dev);
	const u8 regval = data->vregs[reg - 0x10];
	u32 voltage = 0;

	switch (reg) {
	case LTC4245_12VIN:
	case LTC4245_12VOUT:
		voltage = regval * 55;
		break;
	case LTC4245_5VIN:
	case LTC4245_5VOUT:
		voltage = regval * 22;
		break;
	case LTC4245_3VIN:
	case LTC4245_3VOUT:
		voltage = regval * 15;
		break;
	case LTC4245_VEEIN:
	case LTC4245_VEEOUT:
		voltage = regval * -55;
		break;
	case LTC4245_GPIOADC:
		voltage = regval * 10;
		break;
	default:
		/* If we get here, the developer messed up */
		WARN_ON_ONCE(1);
		break;
	}

	return voltage;
}