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
typedef  int u16 ;
struct nand_sdr_timings {int tRC_min; int tCLS_min; int tCLH_min; int tCS_min; int tCH_min; int tWP_min; int tALS_min; int tALH_min; int tDS_min; int tDH_min; int tWC_min; int tWH_min; int tRR_min; int tRP_min; int tREH_min; } ;
struct nand_data_interface {int dummy; } ;
struct nand_chip {int dummy; } ;
struct mxc_nand_host {int /*<<< orphan*/  dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct nand_sdr_timings const*) ; 
 int NAND_DATA_IFACE_CHECK_ONLY ; 
 int /*<<< orphan*/  NFC_V1_V2_CONFIG1 ; 
 int NFC_V2_CONFIG1_ONE_CYCLE ; 
 unsigned long clk_round_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 struct mxc_nand_host* nand_get_controller_data (struct nand_chip*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (struct nand_data_interface const*) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxc_nand_v2_setup_data_interface(struct nand_chip *chip, int csline,
					const struct nand_data_interface *conf)
{
	struct mxc_nand_host *host = nand_get_controller_data(chip);
	int tRC_min_ns, tRC_ps, ret;
	unsigned long rate, rate_round;
	const struct nand_sdr_timings *timings;
	u16 config1;

	timings = nand_get_sdr_timings(conf);
	if (IS_ERR(timings))
		return -ENOTSUPP;

	config1 = readw(NFC_V1_V2_CONFIG1);

	tRC_min_ns = timings->tRC_min / 1000;
	rate = 1000000000 / tRC_min_ns;

	/*
	 * For tRC < 30ns we have to use EDO mode. In this case the controller
	 * does one access per clock cycle. Otherwise the controller does one
	 * access in two clock cycles, thus we have to double the rate to the
	 * controller.
	 */
	if (tRC_min_ns < 30) {
		rate_round = clk_round_rate(host->clk, rate);
		config1 |= NFC_V2_CONFIG1_ONE_CYCLE;
		tRC_ps = 1000000000 / (rate_round / 1000);
	} else {
		rate *= 2;
		rate_round = clk_round_rate(host->clk, rate);
		config1 &= ~NFC_V2_CONFIG1_ONE_CYCLE;
		tRC_ps = 1000000000 / (rate_round / 1000 / 2);
	}

	/*
	 * The timing values compared against are from the i.MX25 Automotive
	 * datasheet, Table 50. NFC Timing Parameters
	 */
	if (timings->tCLS_min > tRC_ps - 1000 ||
	    timings->tCLH_min > tRC_ps - 2000 ||
	    timings->tCS_min > tRC_ps - 1000 ||
	    timings->tCH_min > tRC_ps - 2000 ||
	    timings->tWP_min > tRC_ps - 1500 ||
	    timings->tALS_min > tRC_ps ||
	    timings->tALH_min > tRC_ps - 3000 ||
	    timings->tDS_min > tRC_ps ||
	    timings->tDH_min > tRC_ps - 5000 ||
	    timings->tWC_min > 2 * tRC_ps ||
	    timings->tWH_min > tRC_ps - 2500 ||
	    timings->tRR_min > 6 * tRC_ps ||
	    timings->tRP_min > 3 * tRC_ps / 2 ||
	    timings->tRC_min > 2 * tRC_ps ||
	    timings->tREH_min > (tRC_ps / 2) - 2500) {
		dev_dbg(host->dev, "Timing out of bounds\n");
		return -EINVAL;
	}

	if (csline == NAND_DATA_IFACE_CHECK_ONLY)
		return 0;

	ret = clk_set_rate(host->clk, rate);
	if (ret)
		return ret;

	writew(config1, NFC_V1_V2_CONFIG1);

	dev_dbg(host->dev, "Setting rate to %ldHz, %s mode\n", rate_round,
		config1 & NFC_V2_CONFIG1_ONE_CYCLE ? "One cycle (EDO)" :
		"normal");

	return 0;
}