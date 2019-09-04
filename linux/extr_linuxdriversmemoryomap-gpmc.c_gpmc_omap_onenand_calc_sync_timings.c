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
struct gpmc_settings {int /*<<< orphan*/  sync_write; } ;
struct gpmc_device_timings {int t_avdp_w; int t_wpl; int t_wph; int t_aavdh; int ce_xdelay; int avd_xdelay; int oe_xdelay; int we_xdelay; int clk; int t_bacc; int t_ces; int t_avds; int t_avdh; int t_ach; int cyc_iaa; int t_cez_r; int t_cez_w; int cyc_aavdh_oe; int t_rdyo; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  gpmc_calc_timings (struct gpmc_timings*,struct gpmc_settings*,struct gpmc_device_timings*) ; 
 int max (int const,int const) ; 
 int /*<<< orphan*/  memset (struct gpmc_device_timings*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gpmc_omap_onenand_calc_sync_timings(struct gpmc_timings *t,
						struct gpmc_settings *s,
						int freq, int latency)
{
	struct gpmc_device_timings dev_t;
	const int t_cer  = 15;
	const int t_avdp = 12;
	const int t_cez  = 20; /* max of t_cez, t_oez */
	const int t_wpl  = 40;
	const int t_wph  = 30;
	int min_gpmc_clk_period, t_ces, t_avds, t_avdh, t_ach, t_aavdh, t_rdyo;

	switch (freq) {
	case 104:
		min_gpmc_clk_period = 9600; /* 104 MHz */
		t_ces   = 3;
		t_avds  = 4;
		t_avdh  = 2;
		t_ach   = 3;
		t_aavdh = 6;
		t_rdyo  = 6;
		break;
	case 83:
		min_gpmc_clk_period = 12000; /* 83 MHz */
		t_ces   = 5;
		t_avds  = 4;
		t_avdh  = 2;
		t_ach   = 6;
		t_aavdh = 6;
		t_rdyo  = 9;
		break;
	case 66:
		min_gpmc_clk_period = 15000; /* 66 MHz */
		t_ces   = 6;
		t_avds  = 5;
		t_avdh  = 2;
		t_ach   = 6;
		t_aavdh = 6;
		t_rdyo  = 11;
		break;
	default:
		min_gpmc_clk_period = 18500; /* 54 MHz */
		t_ces   = 7;
		t_avds  = 7;
		t_avdh  = 7;
		t_ach   = 9;
		t_aavdh = 7;
		t_rdyo  = 15;
		break;
	}

	/* Set synchronous read timings */
	memset(&dev_t, 0, sizeof(dev_t));

	if (!s->sync_write) {
		dev_t.t_avdp_w = max(t_avdp, t_cer) * 1000;
		dev_t.t_wpl = t_wpl * 1000;
		dev_t.t_wph = t_wph * 1000;
		dev_t.t_aavdh = t_aavdh * 1000;
	}
	dev_t.ce_xdelay = true;
	dev_t.avd_xdelay = true;
	dev_t.oe_xdelay = true;
	dev_t.we_xdelay = true;
	dev_t.clk = min_gpmc_clk_period;
	dev_t.t_bacc = dev_t.clk;
	dev_t.t_ces = t_ces * 1000;
	dev_t.t_avds = t_avds * 1000;
	dev_t.t_avdh = t_avdh * 1000;
	dev_t.t_ach = t_ach * 1000;
	dev_t.cyc_iaa = (latency + 1);
	dev_t.t_cez_r = t_cez * 1000;
	dev_t.t_cez_w = dev_t.t_cez_r;
	dev_t.cyc_aavdh_oe = 1;
	dev_t.t_rdyo = t_rdyo * 1000 + min_gpmc_clk_period;

	gpmc_calc_timings(t, s, &dev_t);
}