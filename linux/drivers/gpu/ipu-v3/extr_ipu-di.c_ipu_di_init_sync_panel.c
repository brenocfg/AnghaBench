#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int hactive; int flags; int /*<<< orphan*/  pixelclock; int /*<<< orphan*/  vactive; } ;
struct ipu_di_signal_cfg {int hsync_pin; int vsync_pin; scalar_t__ data_pol; scalar_t__ enable_pol; scalar_t__ clk_pol; TYPE_2__ mode; } ;
struct ipu_di {int id; int /*<<< orphan*/  clk_di; int /*<<< orphan*/  clk_ipu; TYPE_1__* ipu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_HSYNC_HIGH ; 
 int DISPLAY_FLAGS_INTERLACED ; 
 int DISPLAY_FLAGS_VSYNC_HIGH ; 
 int /*<<< orphan*/  DI_BS_CLKGEN0 ; 
 int /*<<< orphan*/  DI_BS_CLKGEN1 ; 
 int /*<<< orphan*/  DI_GENERAL ; 
 int DI_GEN_DI_CLK_EXT ; 
 int DI_GEN_DI_VSYNC_EXT ; 
 int DI_GEN_POLARITY_DISP_CLK ; 
 int /*<<< orphan*/  DI_PIN15 ; 
 int /*<<< orphan*/  DI_POL ; 
 int DI_POL_DRDY_DATA_POLARITY ; 
 int DI_POL_DRDY_POLARITY_15 ; 
 int /*<<< orphan*/  DI_SYNC_AS_GEN ; 
 int DI_VSYNC_SEL_OFFSET ; 
 int /*<<< orphan*/  SYNC_WAVE ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_mutex ; 
 int /*<<< orphan*/  ipu_di_config_clock (struct ipu_di*,struct ipu_di_signal_cfg*) ; 
 int /*<<< orphan*/  ipu_di_data_pin_config (struct ipu_di*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ipu_di_data_wave_config (struct ipu_di*,int /*<<< orphan*/ ,int,int) ; 
 int ipu_di_gen_polarity (int) ; 
 int ipu_di_read (struct ipu_di*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_di_sync_config_interlaced (struct ipu_di*,struct ipu_di_signal_cfg*) ; 
 int /*<<< orphan*/  ipu_di_sync_config_noninterlaced (struct ipu_di*,struct ipu_di_signal_cfg*,int) ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ipu_di_init_sync_panel(struct ipu_di *di, struct ipu_di_signal_cfg *sig)
{
	u32 reg;
	u32 di_gen, vsync_cnt;
	u32 div;

	dev_dbg(di->ipu->dev, "disp %d: panel size = %d x %d\n",
		di->id, sig->mode.hactive, sig->mode.vactive);

	dev_dbg(di->ipu->dev, "Clocks: IPU %luHz DI %luHz Needed %luHz\n",
		clk_get_rate(di->clk_ipu),
		clk_get_rate(di->clk_di),
		sig->mode.pixelclock);

	mutex_lock(&di_mutex);

	ipu_di_config_clock(di, sig);

	div = ipu_di_read(di, DI_BS_CLKGEN0) & 0xfff;
	div = div / 16;		/* Now divider is integer portion */

	/* Setup pixel clock timing */
	/* Down time is half of period */
	ipu_di_write(di, (div << 16), DI_BS_CLKGEN1);

	ipu_di_data_wave_config(di, SYNC_WAVE, div - 1, div - 1);
	ipu_di_data_pin_config(di, SYNC_WAVE, DI_PIN15, 3, 0, div * 2);

	di_gen = ipu_di_read(di, DI_GENERAL) & DI_GEN_DI_CLK_EXT;
	di_gen |= DI_GEN_DI_VSYNC_EXT;

	if (sig->mode.flags & DISPLAY_FLAGS_INTERLACED) {
		ipu_di_sync_config_interlaced(di, sig);

		/* set y_sel = 1 */
		di_gen |= 0x10000000;

		vsync_cnt = 3;
	} else {
		ipu_di_sync_config_noninterlaced(di, sig, div);

		vsync_cnt = 3;
		if (di->id == 1)
			/*
			 * TODO: change only for TVEv2, parallel display
			 * uses pin 2 / 3
			 */
			if (!(sig->hsync_pin == 2 && sig->vsync_pin == 3))
				vsync_cnt = 6;
	}

	if (sig->mode.flags & DISPLAY_FLAGS_HSYNC_HIGH)
		di_gen |= ipu_di_gen_polarity(sig->hsync_pin);
	if (sig->mode.flags & DISPLAY_FLAGS_VSYNC_HIGH)
		di_gen |= ipu_di_gen_polarity(sig->vsync_pin);

	if (sig->clk_pol)
		di_gen |= DI_GEN_POLARITY_DISP_CLK;

	ipu_di_write(di, di_gen, DI_GENERAL);

	ipu_di_write(di, (--vsync_cnt << DI_VSYNC_SEL_OFFSET) | 0x00000002,
		     DI_SYNC_AS_GEN);

	reg = ipu_di_read(di, DI_POL);
	reg &= ~(DI_POL_DRDY_DATA_POLARITY | DI_POL_DRDY_POLARITY_15);

	if (sig->enable_pol)
		reg |= DI_POL_DRDY_POLARITY_15;
	if (sig->data_pol)
		reg |= DI_POL_DRDY_DATA_POLARITY;

	ipu_di_write(di, reg, DI_POL);

	mutex_unlock(&di_mutex);

	return 0;
}