#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct amd_northbridge {TYPE_4__* misc; } ;
struct amd64_pvt {int fam; int model; TYPE_3__* ranges; struct pci_dev* F1; } ;
struct TYPE_8__ {int /*<<< orphan*/  vendor; } ;
struct TYPE_6__ {int lo; int hi; } ;
struct TYPE_5__ {int lo; int hi; } ;
struct TYPE_7__ {TYPE_2__ lim; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ DRAM_BASE_HI ; 
 scalar_t__ DRAM_BASE_LO ; 
 scalar_t__ DRAM_LIMIT_HI ; 
 scalar_t__ DRAM_LIMIT_LO ; 
 scalar_t__ DRAM_LOCAL_NODE_LIM ; 
 int GENMASK_ULL (int,int /*<<< orphan*/ ) ; 
 unsigned int PCI_DEVICE_ID_AMD_15H_M30H_NB_F1 ; 
 unsigned int PCI_DEVICE_ID_AMD_15H_M60H_NB_F1 ; 
 unsigned int PCI_DEVICE_ID_AMD_15H_NB_F1 ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  amd64_read_pci_cfg (struct pci_dev*,scalar_t__,int*) ; 
 int /*<<< orphan*/  dram_dst_node (struct amd64_pvt*,unsigned int) ; 
 int /*<<< orphan*/  dram_rw (struct amd64_pvt*,unsigned int) ; 
 struct amd_northbridge* node_to_amd_nb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_related_function (int /*<<< orphan*/ ,unsigned int,TYPE_4__*) ; 

__attribute__((used)) static void read_dram_base_limit_regs(struct amd64_pvt *pvt, unsigned range)
{
	struct amd_northbridge *nb;
	struct pci_dev *f1 = NULL;
	unsigned int pci_func;
	int off = range << 3;
	u32 llim;

	amd64_read_pci_cfg(pvt->F1, DRAM_BASE_LO + off,  &pvt->ranges[range].base.lo);
	amd64_read_pci_cfg(pvt->F1, DRAM_LIMIT_LO + off, &pvt->ranges[range].lim.lo);

	if (pvt->fam == 0xf)
		return;

	if (!dram_rw(pvt, range))
		return;

	amd64_read_pci_cfg(pvt->F1, DRAM_BASE_HI + off,  &pvt->ranges[range].base.hi);
	amd64_read_pci_cfg(pvt->F1, DRAM_LIMIT_HI + off, &pvt->ranges[range].lim.hi);

	/* F15h: factor in CC6 save area by reading dst node's limit reg */
	if (pvt->fam != 0x15)
		return;

	nb = node_to_amd_nb(dram_dst_node(pvt, range));
	if (WARN_ON(!nb))
		return;

	if (pvt->model == 0x60)
		pci_func = PCI_DEVICE_ID_AMD_15H_M60H_NB_F1;
	else if (pvt->model == 0x30)
		pci_func = PCI_DEVICE_ID_AMD_15H_M30H_NB_F1;
	else
		pci_func = PCI_DEVICE_ID_AMD_15H_NB_F1;

	f1 = pci_get_related_function(nb->misc->vendor, pci_func, nb->misc);
	if (WARN_ON(!f1))
		return;

	amd64_read_pci_cfg(f1, DRAM_LOCAL_NODE_LIM, &llim);

	pvt->ranges[range].lim.lo &= GENMASK_ULL(15, 0);

				    /* {[39:27],111b} */
	pvt->ranges[range].lim.lo |= ((llim & 0x1fff) << 3 | 0x7) << 16;

	pvt->ranges[range].lim.hi &= GENMASK_ULL(7, 0);

				    /* [47:40] */
	pvt->ranges[range].lim.hi |= llim >> 13;

	pci_dev_put(f1);
}