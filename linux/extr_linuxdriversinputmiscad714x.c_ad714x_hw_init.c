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
struct ad714x_chip {unsigned short l_state; int /*<<< orphan*/  (* read ) (struct ad714x_chip*,int,unsigned short*,int) ;int /*<<< orphan*/  (* write ) (struct ad714x_chip*,int,int) ;TYPE_1__* hw; } ;
struct TYPE_2__ {int** stage_cfg_reg; int* sys_cfg_reg; } ;

/* Variables and functions */
 int AD714X_STAGECFG_REG ; 
 int AD714X_STG_CAL_EN_REG ; 
 int AD714X_SYSCFG_REG ; 
 int STAGE_CFGREG_NUM ; 
 int STAGE_NUM ; 
 int STG_LOW_INT_STA_REG ; 
 int SYS_CFGREG_NUM ; 
 int /*<<< orphan*/  stub1 (struct ad714x_chip*,unsigned short,int) ; 
 int /*<<< orphan*/  stub2 (struct ad714x_chip*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct ad714x_chip*,int,unsigned short*,int) ; 
 int /*<<< orphan*/  stub4 (struct ad714x_chip*,int,int) ; 
 int /*<<< orphan*/  stub5 (struct ad714x_chip*,int,unsigned short*,int) ; 

__attribute__((used)) static void ad714x_hw_init(struct ad714x_chip *ad714x)
{
	int i, j;
	unsigned short reg_base;
	unsigned short data;

	/* configuration CDC and interrupts */

	for (i = 0; i < STAGE_NUM; i++) {
		reg_base = AD714X_STAGECFG_REG + i * STAGE_CFGREG_NUM;
		for (j = 0; j < STAGE_CFGREG_NUM; j++)
			ad714x->write(ad714x, reg_base + j,
					ad714x->hw->stage_cfg_reg[i][j]);
	}

	for (i = 0; i < SYS_CFGREG_NUM; i++)
		ad714x->write(ad714x, AD714X_SYSCFG_REG + i,
			ad714x->hw->sys_cfg_reg[i]);
	for (i = 0; i < SYS_CFGREG_NUM; i++)
		ad714x->read(ad714x, AD714X_SYSCFG_REG + i, &data, 1);

	ad714x->write(ad714x, AD714X_STG_CAL_EN_REG, 0xFFF);

	/* clear all interrupts */
	ad714x->read(ad714x, STG_LOW_INT_STA_REG, &ad714x->l_state, 3);
}