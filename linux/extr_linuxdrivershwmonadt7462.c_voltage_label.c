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
 int ADT7462_PIN19_INPUT ; 
 int ADT7462_PIN21_INPUT ; 
 int ADT7462_PIN22_INPUT ; 
 int /*<<< orphan*/  ADT7462_PIN23 ; 
 int /*<<< orphan*/  ADT7462_PIN24 ; 
 int /*<<< orphan*/  ADT7462_PIN25 ; 
 int /*<<< orphan*/  ADT7462_PIN26 ; 
 int /*<<< orphan*/  ADT7462_PIN28_SHIFT ; 
 int /*<<< orphan*/  ADT7462_PIN28_VOLT ; 
 int ADT7462_PIN7_INPUT ; 
 int ADT7462_PIN8_INPUT ; 
 int ADT7462_VID_INPUT ; 
 int /*<<< orphan*/  MASK_AND_SHIFT (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *voltage_label(struct adt7462_data *data, int which)
{
	switch (which) {
	case 0:
		if (!(data->pin_cfg[0] & ADT7462_PIN7_INPUT))
			return "+12V1";
		break;
	case 1:
		switch (MASK_AND_SHIFT(data->pin_cfg[1], ADT7462_PIN23)) {
		case 0:
			return "Vccp1";
		case 1:
			return "+2.5V";
		case 2:
			return "+1.8V";
		case 3:
			return "+1.5V";
		}
	case 2:
		if (!(data->pin_cfg[1] & ADT7462_PIN22_INPUT))
			return "+12V3";
		break;
	case 3:
		if (!(data->pin_cfg[1] & ADT7462_PIN21_INPUT))
			return "+5V";
		break;
	case 4:
		if (!(data->pin_cfg[0] & ADT7462_DIODE3_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				return "+0.9V";
			return "+1.25V";
		}
		break;
	case 5:
		if (!(data->pin_cfg[0] & ADT7462_DIODE1_INPUT)) {
			if (data->pin_cfg[1] & ADT7462_PIN19_INPUT)
				return "+1.8V";
			return "+2.5V";
		}
		break;
	case 6:
		if (!(data->pin_cfg[1] & ADT7462_PIN13_INPUT))
			return "+3.3V";
		break;
	case 7:
		if (!(data->pin_cfg[1] & ADT7462_PIN8_INPUT))
			return "+12V2";
		break;
	case 8:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN26)) {
		case 0:
			return "Vbatt";
		case 1:
			return "FSB_Vtt";
		}
		break;
	case 9:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN25)) {
		case 0:
			return "+3.3V";
		case 1:
			return "+1.2V1";
		}
		break;
	case 10:
		switch (MASK_AND_SHIFT(data->pin_cfg[2], ADT7462_PIN24)) {
		case 0:
			return "Vccp2";
		case 1:
			return "+2.5V";
		case 2:
			return "+1.8V";
		case 3:
			return "+1.5";
		}
	case 11:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			return "+1.5V ICH";
		break;
	case 12:
		if (data->pin_cfg[3] >> ADT7462_PIN28_SHIFT ==
					ADT7462_PIN28_VOLT &&
		    !(data->pin_cfg[0] & ADT7462_VID_INPUT))
			return "+1.5V 3GPIO";
		break;
	}
	return "N/A";
}