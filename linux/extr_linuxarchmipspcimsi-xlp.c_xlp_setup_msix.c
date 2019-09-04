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
typedef  int uint64_t ;
struct xlp_msi_data {unsigned int msix_alloc_mask; int /*<<< orphan*/  msi_lock; } ;
struct msi_msg {int address_hi; int address_lo; int data; } ;
struct msi_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MSIX_LINK_ADDR (int,int) ; 
 int PIC_PCIE_MSIX_IRQ (int) ; 
 int XLP_MSIXVEC_PER_LINK ; 
 int fls (unsigned int) ; 
 struct xlp_msi_data* irq_get_chip_data (int) ; 
 int irq_set_msi_desc (int,struct msi_desc*) ; 
 int nlm_irq_msixvec (int) ; 
 int nlm_irq_to_xirq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_link_msixirq (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_msi_msg (int,struct msi_msg*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  xlp_config_link_msix (int,int,int) ; 

__attribute__((used)) static int xlp_setup_msix(uint64_t lnkbase, int node, int link,
	struct msi_desc *desc)
{
	struct xlp_msi_data *md;
	struct msi_msg msg;
	unsigned long flags;
	int t, msixvec, lirq, xirq, ret;
	uint64_t msixaddr;

	/* Get MSI data for the link */
	lirq = PIC_PCIE_MSIX_IRQ(link);
	xirq = nlm_irq_to_xirq(node, nlm_link_msixirq(link, 0));
	md = irq_get_chip_data(xirq);
	msixaddr = MSIX_LINK_ADDR(node, link);

	spin_lock_irqsave(&md->msi_lock, flags);
	/* switch the PCIe link to MSI-X mode at the first alloc */
	if (md->msix_alloc_mask == 0)
		xlp_config_link_msix(lnkbase, lirq, msixaddr);

	/* allocate a MSI-X vec, and tell the bridge about it */
	t = fls(md->msix_alloc_mask);
	if (t == XLP_MSIXVEC_PER_LINK) {
		spin_unlock_irqrestore(&md->msi_lock, flags);
		return -ENOMEM;
	}
	md->msix_alloc_mask |= (1u << t);
	spin_unlock_irqrestore(&md->msi_lock, flags);

	xirq += t;
	msixvec = nlm_irq_msixvec(xirq);

	msg.address_hi = msixaddr >> 32;
	msg.address_lo = msixaddr & 0xffffffff;
	msg.data = 0xc00 | msixvec;

	ret = irq_set_msi_desc(xirq, desc);
	if (ret < 0)
		return ret;

	pci_write_msi_msg(xirq, &msg);
	return 0;
}