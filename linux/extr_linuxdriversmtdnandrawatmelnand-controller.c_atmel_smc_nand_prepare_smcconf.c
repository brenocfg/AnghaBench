#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int tRC_min; int tWP_min; int tCLS_min; int tDS_min; int tCLH_min; int tWC_min; int tREH_min; int tRHOH_min; int tRHZ_max; int tRP_min; int tCLR_min; int tADL_min; int tAR_min; int tRR_min; int tWB_max; int /*<<< orphan*/  tWH_min; int /*<<< orphan*/  tDH_min; int /*<<< orphan*/  tALH_min; int /*<<< orphan*/  tCH_min; int /*<<< orphan*/  tALS_min; int /*<<< orphan*/  tCS_min; } ;
struct TYPE_5__ {TYPE_1__ sdr; } ;
struct nand_data_interface {scalar_t__ type; TYPE_2__ timings; } ;
struct atmel_smc_cs_conf {int mode; int /*<<< orphan*/  timings; } ;
struct atmel_nand_controller {int /*<<< orphan*/  mck; } ;
struct TYPE_6__ {int options; int /*<<< orphan*/  controller; } ;
struct atmel_nand {TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_NFSEL ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_TADL_SHIFT ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_TAR_SHIFT ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_TCLR_SHIFT ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_TRR_SHIFT ; 
 int /*<<< orphan*/  ATMEL_HSMC_TIMINGS_TWB_SHIFT ; 
 int ATMEL_SMC_MODE_DBW_16 ; 
 int ATMEL_SMC_MODE_READMODE_NRD ; 
 int ATMEL_SMC_MODE_TDF (int) ; 
 int ATMEL_SMC_MODE_TDFMODE_OPTIMIZED ; 
 int ATMEL_SMC_MODE_TDF_MAX ; 
 int ATMEL_SMC_MODE_TDF_MIN ; 
 int ATMEL_SMC_MODE_WRITEMODE_NWE ; 
 int /*<<< orphan*/  ATMEL_SMC_NCS_RD_SHIFT ; 
 int /*<<< orphan*/  ATMEL_SMC_NCS_WR_SHIFT ; 
 int /*<<< orphan*/  ATMEL_SMC_NRD_SHIFT ; 
 int /*<<< orphan*/  ATMEL_SMC_NWE_SHIFT ; 
 int DIV_ROUND_UP (int,int) ; 
 int ENOTSUPP ; 
 int ERANGE ; 
 int NAND_BUSWIDTH_16 ; 
 scalar_t__ NAND_SDR_IFACE ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  atmel_smc_cs_conf_init (struct atmel_smc_cs_conf*) ; 
 int atmel_smc_cs_conf_set_cycle (struct atmel_smc_cs_conf*,int /*<<< orphan*/ ,int) ; 
 int atmel_smc_cs_conf_set_pulse (struct atmel_smc_cs_conf*,int /*<<< orphan*/ ,int) ; 
 int atmel_smc_cs_conf_set_setup (struct atmel_smc_cs_conf*,int /*<<< orphan*/ ,int) ; 
 int atmel_smc_cs_conf_set_timing (struct atmel_smc_cs_conf*,int /*<<< orphan*/ ,int) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int max3 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct atmel_nand_controller* to_nand_controller (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_smc_nand_prepare_smcconf(struct atmel_nand *nand,
					const struct nand_data_interface *conf,
					struct atmel_smc_cs_conf *smcconf)
{
	u32 ncycles, totalcycles, timeps, mckperiodps;
	struct atmel_nand_controller *nc;
	int ret;

	nc = to_nand_controller(nand->base.controller);

	/* DDR interface not supported. */
	if (conf->type != NAND_SDR_IFACE)
		return -ENOTSUPP;

	/*
	 * tRC < 30ns implies EDO mode. This controller does not support this
	 * mode.
	 */
	if (conf->timings.sdr.tRC_min < 30000)
		return -ENOTSUPP;

	atmel_smc_cs_conf_init(smcconf);

	mckperiodps = NSEC_PER_SEC / clk_get_rate(nc->mck);
	mckperiodps *= 1000;

	/*
	 * Set write pulse timing. This one is easy to extract:
	 *
	 * NWE_PULSE = tWP
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWP_min, mckperiodps);
	totalcycles = ncycles;
	ret = atmel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * The write setup timing depends on the operation done on the NAND.
	 * All operations goes through the same data bus, but the operation
	 * type depends on the address we are writing to (ALE/CLE address
	 * lines).
	 * Since we have no way to differentiate the different operations at
	 * the SMC level, we must consider the worst case (the biggest setup
	 * time among all operation types):
	 *
	 * NWE_SETUP = max(tCLS, tCS, tALS, tDS) - NWE_PULSE
	 */
	timeps = max3(conf->timings.sdr.tCLS_min, conf->timings.sdr.tCS_min,
		      conf->timings.sdr.tALS_min);
	timeps = max(timeps, conf->timings.sdr.tDS_min);
	ncycles = DIV_ROUND_UP(timeps, mckperiodps);
	ncycles = ncycles > totalcycles ? ncycles - totalcycles : 0;
	totalcycles += ncycles;
	ret = atmel_smc_cs_conf_set_setup(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * As for the write setup timing, the write hold timing depends on the
	 * operation done on the NAND:
	 *
	 * NWE_HOLD = max(tCLH, tCH, tALH, tDH, tWH)
	 */
	timeps = max3(conf->timings.sdr.tCLH_min, conf->timings.sdr.tCH_min,
		      conf->timings.sdr.tALH_min);
	timeps = max3(timeps, conf->timings.sdr.tDH_min,
		      conf->timings.sdr.tWH_min);
	ncycles = DIV_ROUND_UP(timeps, mckperiodps);
	totalcycles += ncycles;

	/*
	 * The write cycle timing is directly matching tWC, but is also
	 * dependent on the other timings on the setup and hold timings we
	 * calculated earlier, which gives:
	 *
	 * NWE_CYCLE = max(tWC, NWE_SETUP + NWE_PULSE + NWE_HOLD)
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWC_min, mckperiodps);
	ncycles = max(totalcycles, ncycles);
	ret = atmel_smc_cs_conf_set_cycle(smcconf, ATMEL_SMC_NWE_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * We don't want the CS line to be toggled between each byte/word
	 * transfer to the NAND. The only way to guarantee that is to have the
	 * NCS_{WR,RD}_{SETUP,HOLD} timings set to 0, which in turn means:
	 *
	 * NCS_WR_PULSE = NWE_CYCLE
	 */
	ret = atmel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NCS_WR_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * As for the write setup timing, the read hold timing depends on the
	 * operation done on the NAND:
	 *
	 * NRD_HOLD = max(tREH, tRHOH)
	 */
	timeps = max(conf->timings.sdr.tREH_min, conf->timings.sdr.tRHOH_min);
	ncycles = DIV_ROUND_UP(timeps, mckperiodps);
	totalcycles = ncycles;

	/*
	 * TDF = tRHZ - NRD_HOLD
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRHZ_max, mckperiodps);
	ncycles -= totalcycles;

	/*
	 * In ONFI 4.0 specs, tRHZ has been increased to support EDO NANDs and
	 * we might end up with a config that does not fit in the TDF field.
	 * Just take the max value in this case and hope that the NAND is more
	 * tolerant than advertised.
	 */
	if (ncycles > ATMEL_SMC_MODE_TDF_MAX)
		ncycles = ATMEL_SMC_MODE_TDF_MAX;
	else if (ncycles < ATMEL_SMC_MODE_TDF_MIN)
		ncycles = ATMEL_SMC_MODE_TDF_MIN;

	smcconf->mode |= ATMEL_SMC_MODE_TDF(ncycles) |
			 ATMEL_SMC_MODE_TDFMODE_OPTIMIZED;

	/*
	 * Read pulse timing directly matches tRP:
	 *
	 * NRD_PULSE = tRP
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRP_min, mckperiodps);
	totalcycles += ncycles;
	ret = atmel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NRD_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * The write cycle timing is directly matching tWC, but is also
	 * dependent on the setup and hold timings we calculated earlier,
	 * which gives:
	 *
	 * NRD_CYCLE = max(tRC, NRD_PULSE + NRD_HOLD)
	 *
	 * NRD_SETUP is always 0.
	 */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRC_min, mckperiodps);
	ncycles = max(totalcycles, ncycles);
	ret = atmel_smc_cs_conf_set_cycle(smcconf, ATMEL_SMC_NRD_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/*
	 * We don't want the CS line to be toggled between each byte/word
	 * transfer from the NAND. The only way to guarantee that is to have
	 * the NCS_{WR,RD}_{SETUP,HOLD} timings set to 0, which in turn means:
	 *
	 * NCS_RD_PULSE = NRD_CYCLE
	 */
	ret = atmel_smc_cs_conf_set_pulse(smcconf, ATMEL_SMC_NCS_RD_SHIFT,
					  ncycles);
	if (ret)
		return ret;

	/* Txxx timings are directly matching tXXX ones. */
	ncycles = DIV_ROUND_UP(conf->timings.sdr.tCLR_min, mckperiodps);
	ret = atmel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TCLR_SHIFT,
					   ncycles);
	if (ret)
		return ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tADL_min, mckperiodps);
	ret = atmel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TADL_SHIFT,
					   ncycles);
	/*
	 * Version 4 of the ONFI spec mandates that tADL be at least 400
	 * nanoseconds, but, depending on the master clock rate, 400 ns may not
	 * fit in the tADL field of the SMC reg. We need to relax the check and
	 * accept the -ERANGE return code.
	 *
	 * Note that previous versions of the ONFI spec had a lower tADL_min
	 * (100 or 200 ns). It's not clear why this timing constraint got
	 * increased but it seems most NANDs are fine with values lower than
	 * 400ns, so we should be safe.
	 */
	if (ret && ret != -ERANGE)
		return ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tAR_min, mckperiodps);
	ret = atmel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TAR_SHIFT,
					   ncycles);
	if (ret)
		return ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tRR_min, mckperiodps);
	ret = atmel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TRR_SHIFT,
					   ncycles);
	if (ret)
		return ret;

	ncycles = DIV_ROUND_UP(conf->timings.sdr.tWB_max, mckperiodps);
	ret = atmel_smc_cs_conf_set_timing(smcconf,
					   ATMEL_HSMC_TIMINGS_TWB_SHIFT,
					   ncycles);
	if (ret)
		return ret;

	/* Attach the CS line to the NFC logic. */
	smcconf->timings |= ATMEL_HSMC_TIMINGS_NFSEL;

	/* Set the appropriate data bus width. */
	if (nand->base.options & NAND_BUSWIDTH_16)
		smcconf->mode |= ATMEL_SMC_MODE_DBW_16;

	/* Operate in NRD/NWE READ/WRITEMODE. */
	smcconf->mode |= ATMEL_SMC_MODE_READMODE_NRD |
			 ATMEL_SMC_MODE_WRITEMODE_NWE;

	return 0;
}