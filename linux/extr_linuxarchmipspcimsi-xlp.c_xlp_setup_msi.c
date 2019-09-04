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
typedef  int uint64_t ;
struct xlp_msi_data {unsigned int msi_alloc_mask; int /*<<< orphan*/  msi_lock; } ;
struct msi_msg {int address_hi; int address_lo; int data; } ;
struct msi_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  picbase; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MSI_LINK_ADDR (int,int) ; 
 int PIC_9XX_IRT_PCIE_LINK_INDEX (int) ; 
 int PIC_IRT_PCIE_LINK_INDEX (int) ; 
 int PIC_PCIE_LINK_MSI_IRQ (int) ; 
 int XLP_MSIVEC_PER_LINK ; 
 scalar_t__ cpu_is_xlp9xx () ; 
 int fls (unsigned int) ; 
 struct xlp_msi_data* irq_get_chip_data (int) ; 
 int irq_set_msi_desc (int,struct msi_desc*) ; 
 TYPE_1__* nlm_get_node (int) ; 
 int nlm_irq_to_xirq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_link_msiirq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_pic_init_irt (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  nlm_setup_pic_irq (int,int,int,int) ; 
 int nlm_threads_per_node () ; 
 int /*<<< orphan*/  pci_write_msi_msg (int,struct msi_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xlp_config_link_msi (int,int,int) ; 

__attribute__((used)) static int xlp_setup_msi(uint64_t lnkbase, int node, int link,
	struct msi_desc *desc)
{
	struct xlp_msi_data *md;
	struct msi_msg msg;
	unsigned long flags;
	int msivec, irt, lirq, xirq, ret;
	uint64_t msiaddr;

	/* Get MSI data for the link */
	lirq = PIC_PCIE_LINK_MSI_IRQ(link);
	xirq = nlm_irq_to_xirq(node, nlm_link_msiirq(link, 0));
	md = irq_get_chip_data(xirq);
	msiaddr = MSI_LINK_ADDR(node, link);

	spin_lock_irqsave(&md->msi_lock, flags);
	if (md->msi_alloc_mask == 0) {
		xlp_config_link_msi(lnkbase, lirq, msiaddr);
		/* switch the link IRQ to MSI range */
		if (cpu_is_xlp9xx())
			irt = PIC_9XX_IRT_PCIE_LINK_INDEX(link);
		else
			irt = PIC_IRT_PCIE_LINK_INDEX(link);
		nlm_setup_pic_irq(node, lirq, lirq, irt);
		nlm_pic_init_irt(nlm_get_node(node)->picbase, irt, lirq,
				 node * nlm_threads_per_node(), 1 /*en */);
	}

	/* allocate a MSI vec, and tell the bridge about it */
	msivec = fls(md->msi_alloc_mask);
	if (msivec == XLP_MSIVEC_PER_LINK) {
		spin_unlock_irqrestore(&md->msi_lock, flags);
		return -ENOMEM;
	}
	md->msi_alloc_mask |= (1u << msivec);
	spin_unlock_irqrestore(&md->msi_lock, flags);

	msg.address_hi = msiaddr >> 32;
	msg.address_lo = msiaddr & 0xffffffff;
	msg.data = 0xc00 | msivec;

	xirq = xirq + msivec;		/* msi mapped to global irq space */
	ret = irq_set_msi_desc(xirq, desc);
	if (ret < 0)
		return ret;

	pci_write_msi_msg(xirq, &msg);
	return 0;
}