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
struct adt7462_data {int* pin_cfg; } ;

/* Variables and functions */
 int ADT7462_DIODE1_INPUT ; 
 int ADT7462_DIODE3_INPUT ; 
 int ADT7462_PIN13_INPUT ; 
 int ADT7462_PIN21_INPUT ; 
 int ADT7462_PIN22_INPUT ; 
 int ADT7462_PIN25_VOLT_INPUT ; 
 int ADT7462_PIN26_VOLT_INPUT ; 
 int /*<<< orphan*/  ADT7462_PIN28_SHIFT ; 
 int /*<<< orphan*/  ADT7462_PIN28_VOLT ; 
 int ADT7462_PIN7_INPUT ; 
 int ADT7462_PIN8_INPUT ; 
 int ADT7462_VID_INPUT ; 

__attribute__((used)) static int ADT7462_REG_VOLT_MAX(struct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			return 0x7C;
		break;
	case 1:
		return 0x69;
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			return 0x7F;
		break;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			return 0x7E;
		break;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT))
			return 0x4B;
		break;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT))
			return 0x49;
		break;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			return 0x68;
		break;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			return 0x7D;
		break;
	case 8:
		if (!(data->pin_cfg[2] & ADT7462_PIN26_VOLT_INPUT))
			return 0x6C;
		break;
	case 9:
		if (!(data->pin_cfg[2] & ADT7462_PIN25_VOLT_INPUT))
			return 0x6B;
		break;
	case 10:
		return 0x6A;
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			return 0x50;
		break;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			return 0x4C;
		break;
	}
	return 0;
}