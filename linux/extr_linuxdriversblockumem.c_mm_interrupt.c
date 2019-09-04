#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cardinfo {int flags; unsigned int dma_status; int /*<<< orphan*/  tasklet; TYPE_1__* dev; scalar_t__ csr_remap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int DMASCR_ANY_ERR ; 
 unsigned int DMASCR_CHAIN_COMPLETE ; 
 unsigned int DMASCR_DMA_COMPLETE ; 
 unsigned int DMASCR_ERROR_MASK ; 
 unsigned int DMASCR_MASTER_ABT ; 
 unsigned int DMASCR_PARITY_ERR_DET ; 
 unsigned int DMASCR_PARITY_ERR_REP ; 
 unsigned int DMASCR_SYSTEM_ERR_SIG ; 
 unsigned int DMASCR_TARGET_ABT ; 
 scalar_t__ DMA_STATUS_CTRL ; 
 scalar_t__ ERROR_ADDR_LOG ; 
 scalar_t__ ERROR_CHECK ; 
 scalar_t__ ERROR_COUNT ; 
 scalar_t__ ERROR_DATA_LOG ; 
 scalar_t__ ERROR_SYNDROME ; 
 int /*<<< orphan*/  HW_TRACE (int) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 scalar_t__ MEMCTRLCMD_ERRSTATUS ; 
 int /*<<< orphan*/  PCI_STATUS ; 
 int UM_FLAG_NO_BYTE_STATUS ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dump_dmastat (struct cardinfo*,unsigned int) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (TYPE_1__*,int /*<<< orphan*/ ,unsigned short*) ; 
 int /*<<< orphan*/  pci_write_config_word (TYPE_1__*,int /*<<< orphan*/ ,unsigned short) ; 
 void* readb (scalar_t__) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mm_interrupt(int irq, void *__card)
{
	struct cardinfo *card = (struct cardinfo *) __card;
	unsigned int dma_status;
	unsigned short cfg_status;

HW_TRACE(0x30);

	dma_status = le32_to_cpu(readl(card->csr_remap + DMA_STATUS_CTRL));

	if (!(dma_status & (DMASCR_ERROR_MASK | DMASCR_CHAIN_COMPLETE))) {
		/* interrupt wasn't for me ... */
		return IRQ_NONE;
	}

	/* clear COMPLETION interrupts */
	if (card->flags & UM_FLAG_NO_BYTE_STATUS)
		writel(cpu_to_le32(DMASCR_DMA_COMPLETE|DMASCR_CHAIN_COMPLETE),
		       card->csr_remap + DMA_STATUS_CTRL);
	else
		writeb((DMASCR_DMA_COMPLETE|DMASCR_CHAIN_COMPLETE) >> 16,
		       card->csr_remap + DMA_STATUS_CTRL + 2);

	/* log errors and clear interrupt status */
	if (dma_status & DMASCR_ANY_ERR) {
		unsigned int	data_log1, data_log2;
		unsigned int	addr_log1, addr_log2;
		unsigned char	stat, count, syndrome, check;

		stat = readb(card->csr_remap + MEMCTRLCMD_ERRSTATUS);

		data_log1 = le32_to_cpu(readl(card->csr_remap +
						ERROR_DATA_LOG));
		data_log2 = le32_to_cpu(readl(card->csr_remap +
						ERROR_DATA_LOG + 4));
		addr_log1 = le32_to_cpu(readl(card->csr_remap +
						ERROR_ADDR_LOG));
		addr_log2 = readb(card->csr_remap + ERROR_ADDR_LOG + 4);

		count = readb(card->csr_remap + ERROR_COUNT);
		syndrome = readb(card->csr_remap + ERROR_SYNDROME);
		check = readb(card->csr_remap + ERROR_CHECK);

		dump_dmastat(card, dma_status);

		if (stat & 0x01)
			dev_printk(KERN_ERR, &card->dev->dev,
				"Memory access error detected (err count %d)\n",
				count);
		if (stat & 0x02)
			dev_printk(KERN_ERR, &card->dev->dev,
				"Multi-bit EDC error\n");

		dev_printk(KERN_ERR, &card->dev->dev,
			"Fault Address 0x%02x%08x, Fault Data 0x%08x%08x\n",
			addr_log2, addr_log1, data_log2, data_log1);
		dev_printk(KERN_ERR, &card->dev->dev,
			"Fault Check 0x%02x, Fault Syndrome 0x%02x\n",
			check, syndrome);

		writeb(0, card->csr_remap + ERROR_COUNT);
	}

	if (dma_status & DMASCR_PARITY_ERR_REP) {
		dev_printk(KERN_ERR, &card->dev->dev,
			"PARITY ERROR REPORTED\n");
		pci_read_config_word(card->dev, PCI_STATUS, &cfg_status);
		pci_write_config_word(card->dev, PCI_STATUS, cfg_status);
	}

	if (dma_status & DMASCR_PARITY_ERR_DET) {
		dev_printk(KERN_ERR, &card->dev->dev,
			"PARITY ERROR DETECTED\n");
		pci_read_config_word(card->dev, PCI_STATUS, &cfg_status);
		pci_write_config_word(card->dev, PCI_STATUS, cfg_status);
	}

	if (dma_status & DMASCR_SYSTEM_ERR_SIG) {
		dev_printk(KERN_ERR, &card->dev->dev, "SYSTEM ERROR\n");
		pci_read_config_word(card->dev, PCI_STATUS, &cfg_status);
		pci_write_config_word(card->dev, PCI_STATUS, cfg_status);
	}

	if (dma_status & DMASCR_TARGET_ABT) {
		dev_printk(KERN_ERR, &card->dev->dev, "TARGET ABORT\n");
		pci_read_config_word(card->dev, PCI_STATUS, &cfg_status);
		pci_write_config_word(card->dev, PCI_STATUS, cfg_status);
	}

	if (dma_status & DMASCR_MASTER_ABT) {
		dev_printk(KERN_ERR, &card->dev->dev, "MASTER ABORT\n");
		pci_read_config_word(card->dev, PCI_STATUS, &cfg_status);
		pci_write_config_word(card->dev, PCI_STATUS, cfg_status);
	}

	/* and process the DMA descriptors */
	card->dma_status = dma_status;
	tasklet_schedule(&card->tasklet);

HW_TRACE(0x36);

	return IRQ_HANDLED;
}