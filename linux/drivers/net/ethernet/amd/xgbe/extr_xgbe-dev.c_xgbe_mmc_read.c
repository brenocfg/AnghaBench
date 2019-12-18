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
typedef  int u64 ;
struct xgbe_prv_data {TYPE_1__* vdata; } ;
struct TYPE_2__ {scalar_t__ mmc_64bit; } ;

/* Variables and functions */
#define  MMC_RXJABBERERROR 136 
#define  MMC_RXOCTETCOUNT_GB_LO 135 
#define  MMC_RXOCTETCOUNT_G_LO 134 
#define  MMC_RXOVERSIZE_G 133 
#define  MMC_RXRUNTERROR 132 
#define  MMC_RXUNDERSIZE_G 131 
#define  MMC_RXWATCHDOGERROR 130 
#define  MMC_TXOCTETCOUNT_GB_LO 129 
#define  MMC_TXOCTETCOUNT_G_LO 128 
 int XGMAC_IOREAD (struct xgbe_prv_data*,unsigned int) ; 

__attribute__((used)) static u64 xgbe_mmc_read(struct xgbe_prv_data *pdata, unsigned int reg_lo)
{
	bool read_hi;
	u64 val;

	if (pdata->vdata->mmc_64bit) {
		switch (reg_lo) {
		/* These registers are always 32 bit */
		case MMC_RXRUNTERROR:
		case MMC_RXJABBERERROR:
		case MMC_RXUNDERSIZE_G:
		case MMC_RXOVERSIZE_G:
		case MMC_RXWATCHDOGERROR:
			read_hi = false;
			break;

		default:
			read_hi = true;
		}
	} else {
		switch (reg_lo) {
		/* These registers are always 64 bit */
		case MMC_TXOCTETCOUNT_GB_LO:
		case MMC_TXOCTETCOUNT_G_LO:
		case MMC_RXOCTETCOUNT_GB_LO:
		case MMC_RXOCTETCOUNT_G_LO:
			read_hi = true;
			break;

		default:
			read_hi = false;
		}
	}

	val = XGMAC_IOREAD(pdata, reg_lo);

	if (read_hi)
		val |= ((u64)XGMAC_IOREAD(pdata, reg_lo + 4) << 32);

	return val;
}