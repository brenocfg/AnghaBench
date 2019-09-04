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
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct bnx2x_virtf {int abs_vfid; TYPE_2__* bars; } ;
struct bnx2x_sriov {int total; } ;
struct bnx2x {TYPE_1__* vfdb; struct pci_dev* pdev; } ;
struct TYPE_4__ {int size; scalar_t__ bar; } ;
struct TYPE_3__ {struct bnx2x_sriov sriov; } ;

/* Variables and functions */
 scalar_t__ PCI_IOV_RESOURCES ; 
 int PCI_SRIOV_NUM_BARS ; 
 int pci_resource_len (struct pci_dev*,scalar_t__) ; 
 scalar_t__ pci_resource_start (struct pci_dev*,scalar_t__) ; 

__attribute__((used)) static void bnx2x_vf_set_bars(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	int i, n;
	struct pci_dev *dev = bp->pdev;
	struct bnx2x_sriov *iov = &bp->vfdb->sriov;

	for (i = 0, n = 0; i < PCI_SRIOV_NUM_BARS; i += 2, n++) {
		u64 start = pci_resource_start(dev, PCI_IOV_RESOURCES + i);
		u32 size = pci_resource_len(dev, PCI_IOV_RESOURCES + i);

		size /= iov->total;
		vf->bars[n].bar = start + size * vf->abs_vfid;
		vf->bars[n].size = size;
	}
}