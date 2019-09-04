#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pci_pbm_info {scalar_t__ chip_type; int chip_version; scalar_t__ pbm_regs; TYPE_2__* op; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 scalar_t__ PBM_CHIP_TYPE_TOMATILLO ; 
 int SCHIZO_PCICTRL_DTO_INT ; 
 int SCHIZO_PCICTRL_MRM_PREF ; 
 int SCHIZO_PCICTRL_PARK ; 
 int SCHIZO_PCICTRL_PTO_SHIFT ; 
 int SCHIZO_PCICTRL_RDL_PREF ; 
 int SCHIZO_PCICTRL_RDO_PREF ; 
 int SCHIZO_PCIDIAG_D_INTSYNC ; 
 int SCHIZO_PCIDIAG_D_RETRY ; 
 int SCHIZO_PCIDIAG_D_RTRYARB ; 
 scalar_t__ SCHIZO_PCI_CTRL ; 
 scalar_t__ SCHIZO_PCI_DIAG ; 
 scalar_t__ SCHIZO_PCI_IRQ_RETRY ; 
 int TOMATILLO_IOC_PART_WPENAB ; 
 int TOMATILLO_IOC_PREF_OFF_SHIFT ; 
 int TOMATILLO_IOC_RDLINE_CPENAB ; 
 int TOMATILLO_IOC_RDMULT_CPENAB ; 
 int TOMATILLO_IOC_RDONE_CPENAB ; 
 scalar_t__ TOMATILLO_PCI_IOC_CSR ; 
 int /*<<< orphan*/  of_find_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int upa_readq (scalar_t__) ; 
 int /*<<< orphan*/  upa_writeq (int,scalar_t__) ; 

__attribute__((used)) static void schizo_pbm_hw_init(struct pci_pbm_info *pbm)
{
	u64 tmp;

	upa_writeq(5, pbm->pbm_regs + SCHIZO_PCI_IRQ_RETRY);

	tmp = upa_readq(pbm->pbm_regs + SCHIZO_PCI_CTRL);

	/* Enable arbiter for all PCI slots.  */
	tmp |= 0xff;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO &&
	    pbm->chip_version >= 0x2)
		tmp |= 0x3UL << SCHIZO_PCICTRL_PTO_SHIFT;

	if (!of_find_property(pbm->op->dev.of_node, "no-bus-parking", NULL))
		tmp |= SCHIZO_PCICTRL_PARK;
	else
		tmp &= ~SCHIZO_PCICTRL_PARK;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO &&
	    pbm->chip_version <= 0x1)
		tmp |= SCHIZO_PCICTRL_DTO_INT;
	else
		tmp &= ~SCHIZO_PCICTRL_DTO_INT;

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO)
		tmp |= (SCHIZO_PCICTRL_MRM_PREF |
			SCHIZO_PCICTRL_RDO_PREF |
			SCHIZO_PCICTRL_RDL_PREF);

	upa_writeq(tmp, pbm->pbm_regs + SCHIZO_PCI_CTRL);

	tmp = upa_readq(pbm->pbm_regs + SCHIZO_PCI_DIAG);
	tmp &= ~(SCHIZO_PCIDIAG_D_RTRYARB |
		 SCHIZO_PCIDIAG_D_RETRY |
		 SCHIZO_PCIDIAG_D_INTSYNC);
	upa_writeq(tmp, pbm->pbm_regs + SCHIZO_PCI_DIAG);

	if (pbm->chip_type == PBM_CHIP_TYPE_TOMATILLO) {
		/* Clear prefetch lengths to workaround a bug in
		 * Jalapeno...
		 */
		tmp = (TOMATILLO_IOC_PART_WPENAB |
		       (1 << TOMATILLO_IOC_PREF_OFF_SHIFT) |
		       TOMATILLO_IOC_RDMULT_CPENAB |
		       TOMATILLO_IOC_RDONE_CPENAB |
		       TOMATILLO_IOC_RDLINE_CPENAB);

		upa_writeq(tmp, pbm->pbm_regs + TOMATILLO_PCI_IOC_CSR);
	}
}