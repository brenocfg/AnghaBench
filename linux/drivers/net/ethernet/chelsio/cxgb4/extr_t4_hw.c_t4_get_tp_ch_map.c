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
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 unsigned int CHELSIO_CHIP_VERSION (int /*<<< orphan*/ ) ; 
#define  CHELSIO_T4 130 
#define  CHELSIO_T5 129 
#define  CHELSIO_T6 128 
 int /*<<< orphan*/  MPS_CMN_CTL_A ; 
 int NUMPORTS_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,unsigned int) ; 
 int /*<<< orphan*/  t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 

unsigned int t4_get_tp_ch_map(struct adapter *adap, int pidx)
{
	unsigned int chip_version = CHELSIO_CHIP_VERSION(adap->params.chip);
	unsigned int nports = 1 << NUMPORTS_G(t4_read_reg(adap, MPS_CMN_CTL_A));

	if (pidx >= nports) {
		dev_warn(adap->pdev_dev, "TP Port Index %d >= Nports %d\n",
			 pidx, nports);
		return 0;
	}

	switch (chip_version) {
	case CHELSIO_T4:
	case CHELSIO_T5:
		/* Note that this happens to be the same values as the MPS
		 * Buffer Group Map for these Chips.  But we replicate the code
		 * here because they're really separate concepts.
		 */
		switch (nports) {
		case 1: return 0xf;
		case 2: return 3 << (2 * pidx);
		case 4: return 1 << pidx;
		}
		break;

	case CHELSIO_T6:
		switch (nports) {
		case 1:
		case 2: return 1 << pidx;
		}
		break;
	}

	dev_err(adap->pdev_dev, "Need TP Channel Map for Chip %0x, Nports %d\n",
		chip_version, nports);
	return 0;
}