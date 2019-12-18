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
typedef  int u32 ;
struct intel_spi {int swseq_reg; int writeable; int erase_64k; int swseq_erase; int locked; int* opcodes; scalar_t__ sregs; scalar_t__ base; TYPE_1__* info; int /*<<< orphan*/  pr_num; int /*<<< orphan*/  nregions; scalar_t__ pregs; } ;
struct TYPE_2__ {int type; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  BXT_FREG_NUM ; 
 scalar_t__ BXT_PR ; 
 int /*<<< orphan*/  BXT_PR_NUM ; 
 scalar_t__ BXT_SSFSTS_CTL ; 
 scalar_t__ BYT_BCR ; 
 int BYT_BCR_WPD ; 
 int /*<<< orphan*/  BYT_FREG_NUM ; 
 scalar_t__ BYT_PR ; 
 int /*<<< orphan*/  BYT_PR_NUM ; 
 scalar_t__ BYT_SSFSTS_CTL ; 
 int EINVAL ; 
 int ERASE_64K_OPCODE_MASK ; 
 int ERASE_OPCODE_MASK ; 
 scalar_t__ HSFSTS_CTL ; 
 int HSFSTS_CTL_FLOCKDN ; 
 int HSFSTS_CTL_FSMIE ; 
#define  INTEL_SPI_BXT 130 
#define  INTEL_SPI_BYT 129 
#define  INTEL_SPI_LPT 128 
 int /*<<< orphan*/  LPT_FREG_NUM ; 
 scalar_t__ LPT_PR ; 
 int /*<<< orphan*/  LPT_PR_NUM ; 
 scalar_t__ LPT_SSFSTS_CTL ; 
 scalar_t__ LVSCC ; 
 scalar_t__ OPMENU0 ; 
 scalar_t__ OPMENU1 ; 
 scalar_t__ SSFSTS_CTL ; 
 int SSFSTS_CTL_FSMIE ; 
 scalar_t__ UVSCC ; 
 int /*<<< orphan*/  intel_spi_dump_regs (struct intel_spi*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writeable ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int intel_spi_init(struct intel_spi *ispi)
{
	u32 opmenu0, opmenu1, lvscc, uvscc, val;
	int i;

	switch (ispi->info->type) {
	case INTEL_SPI_BYT:
		ispi->sregs = ispi->base + BYT_SSFSTS_CTL;
		ispi->pregs = ispi->base + BYT_PR;
		ispi->nregions = BYT_FREG_NUM;
		ispi->pr_num = BYT_PR_NUM;
		ispi->swseq_reg = true;

		if (writeable) {
			/* Disable write protection */
			val = readl(ispi->base + BYT_BCR);
			if (!(val & BYT_BCR_WPD)) {
				val |= BYT_BCR_WPD;
				writel(val, ispi->base + BYT_BCR);
				val = readl(ispi->base + BYT_BCR);
			}

			ispi->writeable = !!(val & BYT_BCR_WPD);
		}

		break;

	case INTEL_SPI_LPT:
		ispi->sregs = ispi->base + LPT_SSFSTS_CTL;
		ispi->pregs = ispi->base + LPT_PR;
		ispi->nregions = LPT_FREG_NUM;
		ispi->pr_num = LPT_PR_NUM;
		ispi->swseq_reg = true;
		break;

	case INTEL_SPI_BXT:
		ispi->sregs = ispi->base + BXT_SSFSTS_CTL;
		ispi->pregs = ispi->base + BXT_PR;
		ispi->nregions = BXT_FREG_NUM;
		ispi->pr_num = BXT_PR_NUM;
		ispi->erase_64k = true;
		break;

	default:
		return -EINVAL;
	}

	/* Disable #SMI generation from HW sequencer */
	val = readl(ispi->base + HSFSTS_CTL);
	val &= ~HSFSTS_CTL_FSMIE;
	writel(val, ispi->base + HSFSTS_CTL);

	/*
	 * Determine whether erase operation should use HW or SW sequencer.
	 *
	 * The HW sequencer has a predefined list of opcodes, with only the
	 * erase opcode being programmable in LVSCC and UVSCC registers.
	 * If these registers don't contain a valid erase opcode, erase
	 * cannot be done using HW sequencer.
	 */
	lvscc = readl(ispi->base + LVSCC);
	uvscc = readl(ispi->base + UVSCC);
	if (!(lvscc & ERASE_OPCODE_MASK) || !(uvscc & ERASE_OPCODE_MASK))
		ispi->swseq_erase = true;
	/* SPI controller on Intel BXT supports 64K erase opcode */
	if (ispi->info->type == INTEL_SPI_BXT && !ispi->swseq_erase)
		if (!(lvscc & ERASE_64K_OPCODE_MASK) ||
		    !(uvscc & ERASE_64K_OPCODE_MASK))
			ispi->erase_64k = false;

	/*
	 * Some controllers can only do basic operations using hardware
	 * sequencer. All other operations are supposed to be carried out
	 * using software sequencer.
	 */
	if (ispi->swseq_reg) {
		/* Disable #SMI generation from SW sequencer */
		val = readl(ispi->sregs + SSFSTS_CTL);
		val &= ~SSFSTS_CTL_FSMIE;
		writel(val, ispi->sregs + SSFSTS_CTL);
	}

	/* Check controller's lock status */
	val = readl(ispi->base + HSFSTS_CTL);
	ispi->locked = !!(val & HSFSTS_CTL_FLOCKDN);

	if (ispi->locked) {
		/*
		 * BIOS programs allowed opcodes and then locks down the
		 * register. So read back what opcodes it decided to support.
		 * That's the set we are going to support as well.
		 */
		opmenu0 = readl(ispi->sregs + OPMENU0);
		opmenu1 = readl(ispi->sregs + OPMENU1);

		if (opmenu0 && opmenu1) {
			for (i = 0; i < ARRAY_SIZE(ispi->opcodes) / 2; i++) {
				ispi->opcodes[i] = opmenu0 >> i * 8;
				ispi->opcodes[i + 4] = opmenu1 >> i * 8;
			}
		}
	}

	intel_spi_dump_regs(ispi);

	return 0;
}