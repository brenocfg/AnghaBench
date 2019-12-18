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
struct ad714x_slider_plat {size_t start_stage; int end_stage; } ;
struct ad714x_chip {scalar_t__* amb_reg; scalar_t__* adc_reg; int /*<<< orphan*/ * sensor_val; int /*<<< orphan*/  (* read ) (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ;TYPE_1__* hw; } ;
struct TYPE_2__ {struct ad714x_slider_plat* slider; } ;

/* Variables and functions */
 scalar_t__ CDC_RESULT_S0 ; 
 int PER_STAGE_REG_NUM ; 
 scalar_t__ STAGE0_AMBIENT ; 
 int /*<<< orphan*/  abs (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  stub2 (struct ad714x_chip*,scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static void ad714x_slider_cal_sensor_val(struct ad714x_chip *ad714x, int idx)
{
	struct ad714x_slider_plat *hw = &ad714x->hw->slider[idx];
	int i;

	ad714x->read(ad714x, CDC_RESULT_S0 + hw->start_stage,
			&ad714x->adc_reg[hw->start_stage],
			hw->end_stage - hw->start_stage + 1);

	for (i = hw->start_stage; i <= hw->end_stage; i++) {
		ad714x->read(ad714x, STAGE0_AMBIENT + i * PER_STAGE_REG_NUM,
				&ad714x->amb_reg[i], 1);

		ad714x->sensor_val[i] =
			abs(ad714x->adc_reg[i] - ad714x->amb_reg[i]);
	}
}