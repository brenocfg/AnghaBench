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
struct nand_sdr_timings {int tWHR_min; int tWP_min; int /*<<< orphan*/  tRP_min; int /*<<< orphan*/  tREA_max; int /*<<< orphan*/  tWH_min; int /*<<< orphan*/  tREH_min; int /*<<< orphan*/  tALS_min; int /*<<< orphan*/  tCLS_min; int /*<<< orphan*/  tCLH_min; int /*<<< orphan*/  tALH_min; } ;
struct nand_data_interface {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  nfi_clk; } ;
struct mtk_nfc {TYPE_2__* caps; TYPE_1__ clk; } ;
struct mtd_info {int dummy; } ;
struct TYPE_4__ {int nfi_clk_div; } ;

/* Variables and functions */
 int ACCTIMING (int,int,int,int,int,int,int) ; 
 int DIV_ROUND_UP (int,int) ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int /*<<< orphan*/  NFI_ACCCON ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtd_to_nand (struct mtd_info*) ; 
 struct mtk_nfc* nand_get_controller_data (int /*<<< orphan*/ ) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 
 int /*<<< orphan*/  nfi_writel (struct mtk_nfc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_nfc_setup_data_interface(struct mtd_info *mtd, int csline,
					const struct nand_data_interface *conf)
{
	struct mtk_nfc *nfc = nand_get_controller_data(mtd_to_nand(mtd));
	const struct nand_sdr_timings *timings;
	u32 rate, tpoecs, tprecs, tc2r, tw2r, twh, twst, trlt;

	timings = nand_get_sdr_timings(conf);
	if (IS_ERR(timings))
		return -ENOTSUPP;

	if (csline == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	rate = clk_get_rate(nfc->clk.nfi_clk);
	/* There is a frequency divider in some IPs */
	rate /= nfc->caps->nfi_clk_div;

	/* turn clock rate into KHZ */
	rate /= 1000;

	tpoecs = max(timings->tALH_min, timings->tCLH_min) / 1000;
	tpoecs = DIV_ROUND_UP(tpoecs * rate, 1000000);
	tpoecs &= 0xf;

	tprecs = max(timings->tCLS_min, timings->tALS_min) / 1000;
	tprecs = DIV_ROUND_UP(tprecs * rate, 1000000);
	tprecs &= 0x3f;

	/* sdr interface has no tCR which means CE# low to RE# low */
	tc2r = 0;

	tw2r = timings->tWHR_min / 1000;
	tw2r = DIV_ROUND_UP(tw2r * rate, 1000000);
	tw2r = DIV_ROUND_UP(tw2r - 1, 2);
	tw2r &= 0xf;

	twh = max(timings->tREH_min, timings->tWH_min) / 1000;
	twh = DIV_ROUND_UP(twh * rate, 1000000) - 1;
	twh &= 0xf;

	twst = timings->tWP_min / 1000;
	twst = DIV_ROUND_UP(twst * rate, 1000000) - 1;
	twst &= 0xf;

	trlt = max(timings->tREA_max, timings->tRP_min) / 1000;
	trlt = DIV_ROUND_UP(trlt * rate, 1000000) - 1;
	trlt &= 0xf;

	/*
	 * ACCON: access timing control register
	 * -------------------------------------
	 * 31:28: tpoecs, minimum required time for CS post pulling down after
	 *        accessing the device
	 * 27:22: tprecs, minimum required time for CS pre pulling down before
	 *        accessing the device
	 * 21:16: tc2r, minimum required time from NCEB low to NREB low
	 * 15:12: tw2r, minimum required time from NWEB high to NREB low.
	 * 11:08: twh, write enable hold time
	 * 07:04: twst, write wait states
	 * 03:00: trlt, read wait states
	 */
	trlt = ACCTIMING(tpoecs, tprecs, tc2r, tw2r, twh, twst, trlt);
	nfi_writel(nfc, trlt, NFI_ACCCON);

	return 0;
}