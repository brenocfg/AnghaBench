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
struct ad714x_touchpad_plat {size_t x_start_stage; int x_end_stage; } ;
struct ad714x_chip {scalar_t__* adc_reg; scalar_t__* amb_reg; scalar_t__* sensor_val; int /*<<< orphan*/  (* read ) (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ;TYPE_1__* hw; } ;
struct TYPE_2__ {struct ad714x_touchpad_plat* touchpad; } ;

/* Variables and functions */
 scalar_t__ CDC_RESULT_S0 ; 
 int PER_STAGE_REG_NUM ; 
 scalar_t__ STAGE0_AMBIENT ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static void touchpad_cal_sensor_val(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_touchpad_plat *hw = &ad714x->hw->touchpad[idx];
	int i;

	ad714x->read(ad714x, CDC_RESULT_S0 + hw->x_start_stage,
			&ad714x->adc_reg[hw->x_start_stage],
			hw->x_end_stage - hw->x_start_stage + 1);

	for (i = hw->x_start_stage; i <= hw->x_end_stage; i++) {
		ad714x->read(ad714x, STAGE0_AMBIENT + i * PER_STAGE_REG_NUM,
				&ad714x->amb_reg[i], 1);
		if (ad714x->adc_reg[i] > ad714x->amb_reg[i])
			ad714x->sensor_val[i] =
				ad714x->adc_reg[i] - ad714x->amb_reg[i];
		else
			ad714x->sensor_val[i] = 0;
	}
}