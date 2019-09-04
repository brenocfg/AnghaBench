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
struct pci_pbm_info {unsigned long controller_regs; struct pci_pbm_info* sibling; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long PSYCHO_UEAFSR_BLK ; 
 unsigned long PSYCHO_UEAFSR_BMSK ; 
 unsigned long PSYCHO_UEAFSR_DOFF ; 
 unsigned long PSYCHO_UEAFSR_MID ; 
 unsigned long PSYCHO_UEAFSR_PDRD ; 
 unsigned long PSYCHO_UEAFSR_PDWR ; 
 unsigned long PSYCHO_UEAFSR_PPIO ; 
 unsigned long PSYCHO_UEAFSR_SDRD ; 
 unsigned long PSYCHO_UEAFSR_SDWR ; 
 unsigned long PSYCHO_UEAFSR_SPIO ; 
 unsigned long PSYCHO_UE_AFAR ; 
 unsigned long PSYCHO_UE_AFSR ; 
 int /*<<< orphan*/  UE_ERR ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  psycho_check_iommu_error (struct pci_pbm_info*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t psycho_ue_intr(int irq, void *dev_id)
{
	struct pci_pbm_info *pbm = dev_id;
	unsigned long afsr_reg = pbm->controller_regs + PSYCHO_UE_AFSR;
	unsigned long afar_reg = pbm->controller_regs + PSYCHO_UE_AFAR;
	unsigned long afsr, afar, error_bits;
	int reported;

	/* Latch uncorrectable error status. */
	afar = upa_readq(afar_reg);
	afsr = upa_readq(afsr_reg);

	/* Clear the primary/secondary error status bits. */
	error_bits = afsr &
		(PSYCHO_UEAFSR_PPIO | PSYCHO_UEAFSR_PDRD | PSYCHO_UEAFSR_PDWR |
		 PSYCHO_UEAFSR_SPIO | PSYCHO_UEAFSR_SDRD | PSYCHO_UEAFSR_SDWR);
	if (!error_bits)
		return IRQ_NONE;
	upa_writeq(error_bits, afsr_reg);

	/* Log the error. */
	printk("%s: Uncorrectable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & PSYCHO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & PSYCHO_UEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & PSYCHO_UEAFSR_PDWR) ?
		   "DMA Write" : "???")))));
	printk("%s: bytemask[%04lx] dword_offset[%lx] UPA_MID[%02lx] was_block(%d)\n",
	       pbm->name,
	       (afsr & PSYCHO_UEAFSR_BMSK) >> 32UL,
	       (afsr & PSYCHO_UEAFSR_DOFF) >> 29UL,
	       (afsr & PSYCHO_UEAFSR_MID) >> 24UL,
	       ((afsr & PSYCHO_UEAFSR_BLK) ? 1 : 0));
	printk("%s: UE AFAR [%016lx]\n", pbm->name, afar);
	printk("%s: UE Secondary errors [", pbm->name);
	reported = 0;
	if (afsr & PSYCHO_UEAFSR_SPIO) {
		reported++;
		printk("(PIO)");
	}
	if (afsr & PSYCHO_UEAFSR_SDRD) {
		reported++;
		printk("(DMA Read)");
	}
	if (afsr & PSYCHO_UEAFSR_SDWR) {
		reported++;
		printk("(DMA Write)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	/* Interrogate both IOMMUs for error status. */
	psycho_check_iommu_error(pbm, afsr, afar, UE_ERR);
	if (pbm->sibling)
		psycho_check_iommu_error(pbm->sibling, afsr, afar, UE_ERR);

	return IRQ_HANDLED;
}