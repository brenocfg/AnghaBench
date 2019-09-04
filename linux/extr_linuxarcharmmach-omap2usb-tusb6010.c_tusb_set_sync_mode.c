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
struct gpmc_timings {int dummy; } ;
struct gpmc_device_timings {int clk; int t_bacc; int t_ces; int t_ceasu; unsigned int t_avdasu; int t_ce_avd; unsigned int t_avdp_r; int cyc_aavdh_oe; int cyc_oe; int t_ce_rdyz; unsigned int t_avdp_w; int cyc_aavdh_we; int cyc_wpl; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  gpmc_calc_timings (struct gpmc_timings*,int /*<<< orphan*/ *,struct gpmc_device_timings*) ; 
 int gpmc_cs_set_timings (int /*<<< orphan*/ ,struct gpmc_timings*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct gpmc_device_timings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sync_cs ; 
 int /*<<< orphan*/  tusb_sync ; 

__attribute__((used)) static int tusb_set_sync_mode(unsigned sysclk_ps)
{
	struct gpmc_device_timings dev_t;
	struct gpmc_timings	t;
	unsigned		t_scsnh_advnh = sysclk_ps + 3000;

	memset(&dev_t, 0, sizeof(dev_t));

	dev_t.clk = 11100;
	dev_t.t_bacc = 1000;
	dev_t.t_ces = 1000;
	dev_t.t_ceasu = 8 * 1000;
	dev_t.t_avdasu = t_scsnh_advnh - 7000;
	dev_t.t_ce_avd = 1000;
	dev_t.t_avdp_r = t_scsnh_advnh;
	dev_t.cyc_aavdh_oe = 3;
	dev_t.cyc_oe = 5;
	dev_t.t_ce_rdyz = 7000;
	dev_t.t_avdp_w = t_scsnh_advnh;
	dev_t.cyc_aavdh_we = 3;
	dev_t.cyc_wpl = 6;

	gpmc_calc_timings(&t, &tusb_sync, &dev_t);

	return gpmc_cs_set_timings(sync_cs, &t, &tusb_sync);
}