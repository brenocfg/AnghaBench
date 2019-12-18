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
typedef  int u32 ;
struct titsc {unsigned int bit_xp; int wires; unsigned int bit_xn; unsigned int bit_yn; unsigned int bit_yp; int coordinate_readouts; unsigned int charge_delay; int step_mask; int /*<<< orphan*/  mfd_tscadc; int /*<<< orphan*/  inp_yn; int /*<<< orphan*/  inp_xp; int /*<<< orphan*/  inp_yp; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CHARGECONFIG ; 
 int /*<<< orphan*/  REG_CHARGEDELAY ; 
 int /*<<< orphan*/  REG_IDLECONFIG ; 
 int /*<<< orphan*/  REG_STEPCONFIG (int) ; 
 int /*<<< orphan*/  REG_STEPDELAY (int) ; 
 unsigned int STEPCONFIG_AVG_16 ; 
 unsigned int STEPCONFIG_INM_ADCREFM ; 
 unsigned int STEPCONFIG_INP (int /*<<< orphan*/ ) ; 
 unsigned int STEPCONFIG_INP_AN4 ; 
 unsigned int STEPCONFIG_MODE_HWSYNC ; 
 unsigned int STEPCONFIG_OPENDLY ; 
 unsigned int STEPCONFIG_XNP ; 
 unsigned int STEPCONFIG_YPN ; 
 int TOTAL_STEPS ; 
 int /*<<< orphan*/  am335x_tsc_se_set_cache (int /*<<< orphan*/ ,int) ; 
 unsigned int titsc_readl (struct titsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  titsc_writel (struct titsc*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void titsc_step_config(struct titsc *ts_dev)
{
	unsigned int	config;
	int i;
	int end_step, first_step, tsc_steps;
	u32 stepenable;

	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_xp;
	switch (ts_dev->wires) {
	case 4:
		config |= STEPCONFIG_INP(ts_dev->inp_yp) | ts_dev->bit_xn;
		break;
	case 5:
		config |= ts_dev->bit_yn |
				STEPCONFIG_INP_AN4 | ts_dev->bit_xn |
				ts_dev->bit_yp;
		break;
	case 8:
		config |= STEPCONFIG_INP(ts_dev->inp_yp) | ts_dev->bit_xn;
		break;
	}

	tsc_steps = ts_dev->coordinate_readouts * 2 + 2;
	first_step = TOTAL_STEPS - tsc_steps;
	/* Steps 16 to 16-coordinate_readouts is for X */
	end_step = first_step + tsc_steps;
	for (i = end_step - ts_dev->coordinate_readouts; i < end_step; i++) {
		titsc_writel(ts_dev, REG_STEPCONFIG(i), config);
		titsc_writel(ts_dev, REG_STEPDELAY(i), STEPCONFIG_OPENDLY);
	}

	config = 0;
	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_yn |
			STEPCONFIG_INM_ADCREFM;
	switch (ts_dev->wires) {
	case 4:
		config |= ts_dev->bit_yp | STEPCONFIG_INP(ts_dev->inp_xp);
		break;
	case 5:
		config |= ts_dev->bit_xp | STEPCONFIG_INP_AN4 |
				STEPCONFIG_XNP | STEPCONFIG_YPN;
		break;
	case 8:
		config |= ts_dev->bit_yp | STEPCONFIG_INP(ts_dev->inp_xp);
		break;
	}

	/* 1 ... coordinate_readouts is for Y */
	end_step = first_step + ts_dev->coordinate_readouts;
	for (i = first_step; i < end_step; i++) {
		titsc_writel(ts_dev, REG_STEPCONFIG(i), config);
		titsc_writel(ts_dev, REG_STEPDELAY(i), STEPCONFIG_OPENDLY);
	}

	/* Make CHARGECONFIG same as IDLECONFIG */

	config = titsc_readl(ts_dev, REG_IDLECONFIG);
	titsc_writel(ts_dev, REG_CHARGECONFIG, config);
	titsc_writel(ts_dev, REG_CHARGEDELAY, ts_dev->charge_delay);

	/* coordinate_readouts + 1 ... coordinate_readouts + 2 is for Z */
	config = STEPCONFIG_MODE_HWSYNC |
			STEPCONFIG_AVG_16 | ts_dev->bit_yp |
			ts_dev->bit_xn | STEPCONFIG_INM_ADCREFM |
			STEPCONFIG_INP(ts_dev->inp_xp);
	titsc_writel(ts_dev, REG_STEPCONFIG(end_step), config);
	titsc_writel(ts_dev, REG_STEPDELAY(end_step),
			STEPCONFIG_OPENDLY);

	end_step++;
	config |= STEPCONFIG_INP(ts_dev->inp_yn);
	titsc_writel(ts_dev, REG_STEPCONFIG(end_step), config);
	titsc_writel(ts_dev, REG_STEPDELAY(end_step),
			STEPCONFIG_OPENDLY);

	/* The steps end ... end - readouts * 2 + 2 and bit 0 for TS_Charge */
	stepenable = 1;
	for (i = 0; i < tsc_steps; i++)
		stepenable |= 1 << (first_step + i + 1);

	ts_dev->step_mask = stepenable;
	am335x_tsc_se_set_cache(ts_dev->mfd_tscadc, ts_dev->step_mask);
}