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
typedef  int uint32_t ;
typedef  int u8 ;
struct jz4780_nemc {scalar_t__ base; int /*<<< orphan*/  dev; TYPE_1__* soc_info; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int tas_tah_cycles_max; } ;

/* Variables and functions */
 int NEMC_SMCR_BW_8 ; 
 int NEMC_SMCR_BW_MASK ; 
 int NEMC_SMCR_SMT ; 
 int NEMC_SMCR_TAH_MASK ; 
 int NEMC_SMCR_TAH_SHIFT ; 
 int NEMC_SMCR_TAS_MASK ; 
 int NEMC_SMCR_TAS_SHIFT ; 
 int NEMC_SMCR_TAW_MASK ; 
 int const NEMC_SMCR_TAW_SHIFT ; 
 int NEMC_SMCR_TBP_MASK ; 
 int const NEMC_SMCR_TBP_SHIFT ; 
 int NEMC_SMCR_TSTRV_MASK ; 
 int NEMC_SMCR_TSTRV_SHIFT ; 
 scalar_t__ NEMC_SMCRn (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int jz4780_nemc_ns_to_cycles (struct jz4780_nemc*,int) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static bool jz4780_nemc_configure_bank(struct jz4780_nemc *nemc,
				       unsigned int bank,
				       struct device_node *node)
{
	uint32_t smcr, val, cycles;

	/*
	 * Conversion of tBP and tAW cycle counts to values supported by the
	 * hardware (round up to the next supported value).
	 */
	static const u8 convert_tBP_tAW[] = {
		0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,

		/* 11 - 12 -> 12 cycles */
		11, 11,

		/* 13 - 15 -> 15 cycles */
		12, 12, 12,

		/* 16 - 20 -> 20 cycles */
		13, 13, 13, 13, 13,

		/* 21 - 25 -> 25 cycles */
		14, 14, 14, 14, 14,

		/* 26 - 31 -> 31 cycles */
		15, 15, 15, 15, 15, 15
	};

	smcr = readl(nemc->base + NEMC_SMCRn(bank));
	smcr &= ~NEMC_SMCR_SMT;

	if (!of_property_read_u32(node, "ingenic,nemc-bus-width", &val)) {
		smcr &= ~NEMC_SMCR_BW_MASK;
		switch (val) {
		case 8:
			smcr |= NEMC_SMCR_BW_8;
			break;
		default:
			/*
			 * Earlier SoCs support a 16 bit bus width (the 4780
			 * does not), until those are properly supported, error.
			 */
			dev_err(nemc->dev, "unsupported bus width: %u\n", val);
			return false;
		}
	}

	if (of_property_read_u32(node, "ingenic,nemc-tAS", &val) == 0) {
		smcr &= ~NEMC_SMCR_TAS_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		if (cycles > nemc->soc_info->tas_tah_cycles_max) {
			dev_err(nemc->dev, "tAS %u is too high (%u cycles)\n",
				val, cycles);
			return false;
		}

		smcr |= cycles << NEMC_SMCR_TAS_SHIFT;
	}

	if (of_property_read_u32(node, "ingenic,nemc-tAH", &val) == 0) {
		smcr &= ~NEMC_SMCR_TAH_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		if (cycles > nemc->soc_info->tas_tah_cycles_max) {
			dev_err(nemc->dev, "tAH %u is too high (%u cycles)\n",
				val, cycles);
			return false;
		}

		smcr |= cycles << NEMC_SMCR_TAH_SHIFT;
	}

	if (of_property_read_u32(node, "ingenic,nemc-tBP", &val) == 0) {
		smcr &= ~NEMC_SMCR_TBP_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		if (cycles > 31) {
			dev_err(nemc->dev, "tBP %u is too high (%u cycles)\n",
				val, cycles);
			return false;
		}

		smcr |= convert_tBP_tAW[cycles] << NEMC_SMCR_TBP_SHIFT;
	}

	if (of_property_read_u32(node, "ingenic,nemc-tAW", &val) == 0) {
		smcr &= ~NEMC_SMCR_TAW_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		if (cycles > 31) {
			dev_err(nemc->dev, "tAW %u is too high (%u cycles)\n",
				val, cycles);
			return false;
		}

		smcr |= convert_tBP_tAW[cycles] << NEMC_SMCR_TAW_SHIFT;
	}

	if (of_property_read_u32(node, "ingenic,nemc-tSTRV", &val) == 0) {
		smcr &= ~NEMC_SMCR_TSTRV_MASK;
		cycles = jz4780_nemc_ns_to_cycles(nemc, val);
		if (cycles > 63) {
			dev_err(nemc->dev, "tSTRV %u is too high (%u cycles)\n",
				val, cycles);
			return false;
		}

		smcr |= cycles << NEMC_SMCR_TSTRV_SHIFT;
	}

	writel(smcr, nemc->base + NEMC_SMCRn(bank));
	return true;
}