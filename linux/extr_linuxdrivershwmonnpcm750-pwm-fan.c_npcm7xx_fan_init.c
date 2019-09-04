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
typedef  int u32 ;
struct npcm7xx_pwm_fan_data {int input_clk_freq; int /*<<< orphan*/  fan_clk; TYPE_1__* fan_dev; int /*<<< orphan*/  fan_base; } ;
struct TYPE_2__ {scalar_t__ fan_cnt; int /*<<< orphan*/  fan_pls_per_rev; int /*<<< orphan*/  fan_st_flg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAN_DISABLE ; 
 int NPCM7XX_FAN_CLK_PRESCALE ; 
 int /*<<< orphan*/  NPCM7XX_FAN_DEFAULT_PULSE_PER_REVOLUTION ; 
 int NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE ; 
 int NPCM7XX_FAN_MAX_MODULE ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCKC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCNT1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCNT2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCPA (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCPB (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TCPCFG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TICLR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TIEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TINASEL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TINBSEL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TMCTRL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NPCM7XX_FAN_REG_TPRSC (int /*<<< orphan*/ ,int) ; 
 int NPCM7XX_FAN_TCKC_CLKX_NONE ; 
 int /*<<< orphan*/  NPCM7XX_FAN_TCNT ; 
 int /*<<< orphan*/  NPCM7XX_FAN_TCPA ; 
 int /*<<< orphan*/  NPCM7XX_FAN_TCPB ; 
 int NPCM7XX_FAN_TCPCFG_EQAEN ; 
 int NPCM7XX_FAN_TCPCFG_EQBEN ; 
 int NPCM7XX_FAN_TICLR_CLEAR_ALL ; 
 int NPCM7XX_FAN_TINASEL_FANIN_DEFAULT ; 
 int NPCM7XX_FAN_TMCTRL_MODE_5 ; 
 int NPCM7XX_FAN_TMCTRL_TAEN ; 
 int NPCM7XX_FAN_TMCTRL_TBEN ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void npcm7xx_fan_init(struct npcm7xx_pwm_fan_data *data)
{
	int md;
	int ch;
	int i;
	u32 apb_clk_freq;

	for (md = 0; md < NPCM7XX_FAN_MAX_MODULE; md++) {
		/* stop FAN0~7 clock */
		iowrite8(NPCM7XX_FAN_TCKC_CLKX_NONE,
			 NPCM7XX_FAN_REG_TCKC(data->fan_base, md));

		/* disable all interrupt */
		iowrite8(0x00, NPCM7XX_FAN_REG_TIEN(data->fan_base, md));

		/* clear all interrupt */
		iowrite8(NPCM7XX_FAN_TICLR_CLEAR_ALL,
			 NPCM7XX_FAN_REG_TICLR(data->fan_base, md));

		/* set FAN0~7 clock prescaler */
		iowrite8(NPCM7XX_FAN_CLK_PRESCALE,
			 NPCM7XX_FAN_REG_TPRSC(data->fan_base, md));

		/* set FAN0~7 mode (high-to-low transition) */
		iowrite8((NPCM7XX_FAN_TMCTRL_MODE_5 | NPCM7XX_FAN_TMCTRL_TBEN |
			  NPCM7XX_FAN_TMCTRL_TAEN),
			 NPCM7XX_FAN_REG_TMCTRL(data->fan_base, md));

		/* set FAN0~7 Initial Count/Cap */
		iowrite16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_REG_TCNT1(data->fan_base, md));
		iowrite16(NPCM7XX_FAN_TCNT,
			  NPCM7XX_FAN_REG_TCNT2(data->fan_base, md));

		/* set FAN0~7 compare (equal to count) */
		iowrite8((NPCM7XX_FAN_TCPCFG_EQAEN | NPCM7XX_FAN_TCPCFG_EQBEN),
			 NPCM7XX_FAN_REG_TCPCFG(data->fan_base, md));

		/* set FAN0~7 compare value */
		iowrite16(NPCM7XX_FAN_TCPA,
			  NPCM7XX_FAN_REG_TCPA(data->fan_base, md));
		iowrite16(NPCM7XX_FAN_TCPB,
			  NPCM7XX_FAN_REG_TCPB(data->fan_base, md));

		/* set FAN0~7 fan input FANIN 0~15 */
		iowrite8(NPCM7XX_FAN_TINASEL_FANIN_DEFAULT,
			 NPCM7XX_FAN_REG_TINASEL(data->fan_base, md));
		iowrite8(NPCM7XX_FAN_TINASEL_FANIN_DEFAULT,
			 NPCM7XX_FAN_REG_TINBSEL(data->fan_base, md));

		for (i = 0; i < NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE; i++) {
			ch = md * NPCM7XX_FAN_MAX_CHN_NUM_IN_A_MODULE + i;
			data->fan_dev[ch].fan_st_flg = FAN_DISABLE;
			data->fan_dev[ch].fan_pls_per_rev =
				NPCM7XX_FAN_DEFAULT_PULSE_PER_REVOLUTION;
			data->fan_dev[ch].fan_cnt = 0;
		}
	}

	apb_clk_freq = clk_get_rate(data->fan_clk);

	/* Fan tach input clock = APB clock / prescalar, default is 255. */
	data->input_clk_freq = apb_clk_freq / (NPCM7XX_FAN_CLK_PRESCALE + 1);
}