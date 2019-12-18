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
struct nand_sdr_timings {int tRC_min; int tAR_min; int tCLR_min; int tCS_min; int tWP_min; int tDH_min; int tCH_min; int tCLH_min; int tWH_min; int tALH_min; int tREH_min; int tRP_min; int tCEA_max; int tREA_max; } ;
struct fsmc_nand_timings {scalar_t__ tar; scalar_t__ tclr; scalar_t__ thold; scalar_t__ twait; scalar_t__ tset; void* thiz; } ;
struct fsmc_nand_data {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 void* DIV_ROUND_UP (int,unsigned long) ; 
 int EOPNOTSUPP ; 
 scalar_t__ FSMC_TAR_MASK ; 
 scalar_t__ FSMC_TCLR_MASK ; 
 int FSMC_THOLD_MASK ; 
 int FSMC_TSET_MASK ; 
 int FSMC_TWAIT_MASK ; 
 unsigned long NSEC_PER_SEC ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 

__attribute__((used)) static int fsmc_calc_timings(struct fsmc_nand_data *host,
			     const struct nand_sdr_timings *sdrt,
			     struct fsmc_nand_timings *tims)
{
	unsigned long hclk = clk_get_rate(host->clk);
	unsigned long hclkn = NSEC_PER_SEC / hclk;
	u32 thiz, thold, twait, tset;

	if (sdrt->tRC_min < 30000)
		return -EOPNOTSUPP;

	tims->tar = DIV_ROUND_UP(sdrt->tAR_min / 1000, hclkn) - 1;
	if (tims->tar > FSMC_TAR_MASK)
		tims->tar = FSMC_TAR_MASK;
	tims->tclr = DIV_ROUND_UP(sdrt->tCLR_min / 1000, hclkn) - 1;
	if (tims->tclr > FSMC_TCLR_MASK)
		tims->tclr = FSMC_TCLR_MASK;

	thiz = sdrt->tCS_min - sdrt->tWP_min;
	tims->thiz = DIV_ROUND_UP(thiz / 1000, hclkn);

	thold = sdrt->tDH_min;
	if (thold < sdrt->tCH_min)
		thold = sdrt->tCH_min;
	if (thold < sdrt->tCLH_min)
		thold = sdrt->tCLH_min;
	if (thold < sdrt->tWH_min)
		thold = sdrt->tWH_min;
	if (thold < sdrt->tALH_min)
		thold = sdrt->tALH_min;
	if (thold < sdrt->tREH_min)
		thold = sdrt->tREH_min;
	tims->thold = DIV_ROUND_UP(thold / 1000, hclkn);
	if (tims->thold == 0)
		tims->thold = 1;
	else if (tims->thold > FSMC_THOLD_MASK)
		tims->thold = FSMC_THOLD_MASK;

	twait = max(sdrt->tRP_min, sdrt->tWP_min);
	tims->twait = DIV_ROUND_UP(twait / 1000, hclkn) - 1;
	if (tims->twait == 0)
		tims->twait = 1;
	else if (tims->twait > FSMC_TWAIT_MASK)
		tims->twait = FSMC_TWAIT_MASK;

	tset = max(sdrt->tCS_min - sdrt->tWP_min,
		   sdrt->tCEA_max - sdrt->tREA_max);
	tims->tset = DIV_ROUND_UP(tset / 1000, hclkn) - 1;
	if (tims->tset == 0)
		tims->tset = 1;
	else if (tims->tset > FSMC_TSET_MASK)
		tims->tset = FSMC_TSET_MASK;

	return 0;
}