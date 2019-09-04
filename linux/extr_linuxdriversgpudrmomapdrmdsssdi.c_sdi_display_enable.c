#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct videomode {int flags; unsigned long pixelclock; } ;
struct TYPE_10__ {int /*<<< orphan*/  dispc_channel; int /*<<< orphan*/  dispc_channel_connected; } ;
struct dispc_clock_info {unsigned long lck_div; unsigned long pck_div; } ;
struct TYPE_8__ {struct dispc_clock_info clock_info; } ;
struct sdi_device {int /*<<< orphan*/  vdds_sdi_reg; TYPE_2__* dss; TYPE_6__ output; int /*<<< orphan*/  datapairs; TYPE_1__ mgr_config; struct videomode vm; } ;
struct omap_dss_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  dispc; } ;

/* Variables and functions */
 int DISPLAY_FLAGS_PIXDATA_POSEDGE ; 
 int DISPLAY_FLAGS_SYNC_POSEDGE ; 
 int /*<<< orphan*/  DSSERR (char*) ; 
 int /*<<< orphan*/  DSSWARN (char*,unsigned long,unsigned long) ; 
 int ENODEV ; 
 int /*<<< orphan*/  dispc_mgr_set_clock_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dispc_clock_info*) ; 
 int dispc_runtime_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dispc_runtime_put (int /*<<< orphan*/ ) ; 
 int dss_mgr_enable (TYPE_6__*) ; 
 int /*<<< orphan*/  dss_mgr_set_timings (TYPE_6__*,struct videomode*) ; 
 int /*<<< orphan*/  dss_sdi_disable (TYPE_2__*) ; 
 int dss_sdi_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  dss_sdi_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dss_set_fck_rate (TYPE_2__*,unsigned long) ; 
 struct sdi_device* dssdev_to_sdi (struct omap_dss_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int sdi_calc_clock_div (struct sdi_device*,unsigned long,unsigned long*,struct dispc_clock_info*) ; 
 int /*<<< orphan*/  sdi_config_lcd_manager (struct sdi_device*) ; 

__attribute__((used)) static int sdi_display_enable(struct omap_dss_device *dssdev)
{
	struct sdi_device *sdi = dssdev_to_sdi(dssdev);
	struct videomode *vm = &sdi->vm;
	unsigned long fck;
	struct dispc_clock_info dispc_cinfo;
	unsigned long pck;
	int r;

	if (!sdi->output.dispc_channel_connected) {
		DSSERR("failed to enable display: no output/manager\n");
		return -ENODEV;
	}

	r = regulator_enable(sdi->vdds_sdi_reg);
	if (r)
		goto err_reg_enable;

	r = dispc_runtime_get(sdi->dss->dispc);
	if (r)
		goto err_get_dispc;

	/* 15.5.9.1.2 */
	vm->flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE | DISPLAY_FLAGS_SYNC_POSEDGE;

	r = sdi_calc_clock_div(sdi, vm->pixelclock, &fck, &dispc_cinfo);
	if (r)
		goto err_calc_clock_div;

	sdi->mgr_config.clock_info = dispc_cinfo;

	pck = fck / dispc_cinfo.lck_div / dispc_cinfo.pck_div;

	if (pck != vm->pixelclock) {
		DSSWARN("Could not find exact pixel clock. Requested %lu Hz, got %lu Hz\n",
			vm->pixelclock, pck);

		vm->pixelclock = pck;
	}


	dss_mgr_set_timings(&sdi->output, vm);

	r = dss_set_fck_rate(sdi->dss, fck);
	if (r)
		goto err_set_dss_clock_div;

	sdi_config_lcd_manager(sdi);

	/*
	 * LCLK and PCLK divisors are located in shadow registers, and we
	 * normally write them to DISPC registers when enabling the output.
	 * However, SDI uses pck-free as source clock for its PLL, and pck-free
	 * is affected by the divisors. And as we need the PLL before enabling
	 * the output, we need to write the divisors early.
	 *
	 * It seems just writing to the DISPC register is enough, and we don't
	 * need to care about the shadow register mechanism for pck-free. The
	 * exact reason for this is unknown.
	 */
	dispc_mgr_set_clock_div(sdi->dss->dispc, sdi->output.dispc_channel,
				&sdi->mgr_config.clock_info);

	dss_sdi_init(sdi->dss, sdi->datapairs);
	r = dss_sdi_enable(sdi->dss);
	if (r)
		goto err_sdi_enable;
	mdelay(2);

	r = dss_mgr_enable(&sdi->output);
	if (r)
		goto err_mgr_enable;

	return 0;

err_mgr_enable:
	dss_sdi_disable(sdi->dss);
err_sdi_enable:
err_set_dss_clock_div:
err_calc_clock_div:
	dispc_runtime_put(sdi->dss->dispc);
err_get_dispc:
	regulator_disable(sdi->vdds_sdi_reg);
err_reg_enable:
	return r;
}