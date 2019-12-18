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
struct intel_spi {int nregions; int pr_num; scalar_t__ swseq_erase; int /*<<< orphan*/  dev; scalar_t__ swseq_reg; scalar_t__ base; scalar_t__ pregs; TYPE_1__* info; scalar_t__ sregs; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ BFPREG ; 
 scalar_t__ BYT_BCR ; 
 scalar_t__ DLOCK ; 
 scalar_t__ FADDR ; 
 scalar_t__ FDATA (int) ; 
 scalar_t__ FRACC ; 
 scalar_t__ FREG (int) ; 
 int FREG_BASE_MASK ; 
 int FREG_LIMIT_MASK ; 
 int FREG_LIMIT_SHIFT ; 
 scalar_t__ HSFSTS_CTL ; 
 int HSFSTS_CTL_FLOCKDN ; 
 scalar_t__ INTEL_SPI_BYT ; 
 scalar_t__ LVSCC ; 
 scalar_t__ OPMENU0 ; 
 scalar_t__ OPMENU1 ; 
 scalar_t__ PR (int) ; 
 scalar_t__ PREOP_OPTYPE ; 
 int PR_BASE_MASK ; 
 int PR_LIMIT_MASK ; 
 int PR_LIMIT_SHIFT ; 
 int PR_RPE ; 
 int PR_WPE ; 
 scalar_t__ SSFSTS_CTL ; 
 scalar_t__ UVSCC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 char readl (scalar_t__) ; 

__attribute__((used)) static void intel_spi_dump_regs(struct intel_spi *ispi)
{
	u32 value;
	int i;

	dev_dbg(ispi->dev, "BFPREG=0x%08x\n", readl(ispi->base + BFPREG));

	value = readl(ispi->base + HSFSTS_CTL);
	dev_dbg(ispi->dev, "HSFSTS_CTL=0x%08x\n", value);
	if (value & HSFSTS_CTL_FLOCKDN)
		dev_dbg(ispi->dev, "-> Locked\n");

	dev_dbg(ispi->dev, "FADDR=0x%08x\n", readl(ispi->base + FADDR));
	dev_dbg(ispi->dev, "DLOCK=0x%08x\n", readl(ispi->base + DLOCK));

	for (i = 0; i < 16; i++)
		dev_dbg(ispi->dev, "FDATA(%d)=0x%08x\n",
			i, readl(ispi->base + FDATA(i)));

	dev_dbg(ispi->dev, "FRACC=0x%08x\n", readl(ispi->base + FRACC));

	for (i = 0; i < ispi->nregions; i++)
		dev_dbg(ispi->dev, "FREG(%d)=0x%08x\n", i,
			readl(ispi->base + FREG(i)));
	for (i = 0; i < ispi->pr_num; i++)
		dev_dbg(ispi->dev, "PR(%d)=0x%08x\n", i,
			readl(ispi->pregs + PR(i)));

	value = readl(ispi->sregs + SSFSTS_CTL);
	dev_dbg(ispi->dev, "SSFSTS_CTL=0x%08x\n", value);
	dev_dbg(ispi->dev, "PREOP_OPTYPE=0x%08x\n",
		readl(ispi->sregs + PREOP_OPTYPE));
	dev_dbg(ispi->dev, "OPMENU0=0x%08x\n", readl(ispi->sregs + OPMENU0));
	dev_dbg(ispi->dev, "OPMENU1=0x%08x\n", readl(ispi->sregs + OPMENU1));

	if (ispi->info->type == INTEL_SPI_BYT)
		dev_dbg(ispi->dev, "BCR=0x%08x\n", readl(ispi->base + BYT_BCR));

	dev_dbg(ispi->dev, "LVSCC=0x%08x\n", readl(ispi->base + LVSCC));
	dev_dbg(ispi->dev, "UVSCC=0x%08x\n", readl(ispi->base + UVSCC));

	dev_dbg(ispi->dev, "Protected regions:\n");
	for (i = 0; i < ispi->pr_num; i++) {
		u32 base, limit;

		value = readl(ispi->pregs + PR(i));
		if (!(value & (PR_WPE | PR_RPE)))
			continue;

		limit = (value & PR_LIMIT_MASK) >> PR_LIMIT_SHIFT;
		base = value & PR_BASE_MASK;

		dev_dbg(ispi->dev, " %02d base: 0x%08x limit: 0x%08x [%c%c]\n",
			 i, base << 12, (limit << 12) | 0xfff,
			 value & PR_WPE ? 'W' : '.',
			 value & PR_RPE ? 'R' : '.');
	}

	dev_dbg(ispi->dev, "Flash regions:\n");
	for (i = 0; i < ispi->nregions; i++) {
		u32 region, base, limit;

		region = readl(ispi->base + FREG(i));
		base = region & FREG_BASE_MASK;
		limit = (region & FREG_LIMIT_MASK) >> FREG_LIMIT_SHIFT;

		if (base >= limit || (i > 0 && limit == 0))
			dev_dbg(ispi->dev, " %02d disabled\n", i);
		else
			dev_dbg(ispi->dev, " %02d base: 0x%08x limit: 0x%08x\n",
				 i, base << 12, (limit << 12) | 0xfff);
	}

	dev_dbg(ispi->dev, "Using %cW sequencer for register access\n",
		ispi->swseq_reg ? 'S' : 'H');
	dev_dbg(ispi->dev, "Using %cW sequencer for erase operation\n",
		ispi->swseq_erase ? 'S' : 'H');
}