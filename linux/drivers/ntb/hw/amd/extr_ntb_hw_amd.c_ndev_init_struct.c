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
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  topo; struct pci_dev* pdev; } ;
struct amd_ntb_dev {int /*<<< orphan*/  db_mask_lock; int /*<<< orphan*/  int_mask; TYPE_1__ ntb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_EVENT_INTMASK ; 
 int /*<<< orphan*/  NTB_TOPO_NONE ; 
 int /*<<< orphan*/  amd_ntb_ops ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ndev_init_struct(struct amd_ntb_dev *ndev,
				    struct pci_dev *pdev)
{
	ndev->ntb.pdev = pdev;
	ndev->ntb.topo = NTB_TOPO_NONE;
	ndev->ntb.ops = &amd_ntb_ops;
	ndev->int_mask = AMD_EVENT_INTMASK;
	spin_lock_init(&ndev->db_mask_lock);
}