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
struct nct6775_data {int* pwm_enable; int tolerance_mask; int* target_speed_tolerance; int* target_speed; int* target_temp; int** temp_tolerance; int /*<<< orphan*/ * REG_FAN_MODE; int /*<<< orphan*/ * REG_TARGET; int /*<<< orphan*/ * REG_TOLERANCE_H; } ;

/* Variables and functions */
#define  manual 131 
 int nct6775_read_value (struct nct6775_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nct6775_write_value (struct nct6775_data*,int /*<<< orphan*/ ,int) ; 
#define  off 130 
#define  speed_cruise 129 
#define  thermal_cruise 128 

__attribute__((used)) static void pwm_update_registers(struct nct6775_data *data, int nr)
{
	u8 reg;

	switch (data->pwm_enable[nr]) {
	case off:
	case manual:
		break;
	case speed_cruise:
		reg = nct6775_read_value(data, data->REG_FAN_MODE[nr]);
		reg = (reg & ~data->tolerance_mask) |
		  (data->target_speed_tolerance[nr] & data->tolerance_mask);
		nct6775_write_value(data, data->REG_FAN_MODE[nr], reg);
		nct6775_write_value(data, data->REG_TARGET[nr],
				    data->target_speed[nr] & 0xff);
		if (data->REG_TOLERANCE_H) {
			reg = (data->target_speed[nr] >> 8) & 0x0f;
			reg |= (data->target_speed_tolerance[nr] & 0x38) << 1;
			nct6775_write_value(data,
					    data->REG_TOLERANCE_H[nr],
					    reg);
		}
		break;
	case thermal_cruise:
		nct6775_write_value(data, data->REG_TARGET[nr],
				    data->target_temp[nr]);
		/* fall through  */
	default:
		reg = nct6775_read_value(data, data->REG_FAN_MODE[nr]);
		reg = (reg & ~data->tolerance_mask) |
		  data->temp_tolerance[0][nr];
		nct6775_write_value(data, data->REG_FAN_MODE[nr], reg);
		break;
	}
}