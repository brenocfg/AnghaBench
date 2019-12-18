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
typedef  int u64 ;
struct vnic_stats {int dummy; } ;
struct vnic_dev {int stats_pa; struct vnic_stats* stats; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STATS_DUMP ; 
 int ENOMEM ; 
 struct vnic_stats* pci_alloc_consistent (int /*<<< orphan*/ ,int,int*) ; 
 int vnic_dev_cmd (struct vnic_dev*,int /*<<< orphan*/ ,int*,int*,int) ; 

int vnic_dev_stats_dump(struct vnic_dev *vdev, struct vnic_stats **stats)
{
	u64 a0, a1;
	int wait = 1000;

	if (!vdev->stats) {
		vdev->stats = pci_alloc_consistent(vdev->pdev,
			sizeof(struct vnic_stats), &vdev->stats_pa);
		if (!vdev->stats)
			return -ENOMEM;
	}

	*stats = vdev->stats;
	a0 = vdev->stats_pa;
	a1 = sizeof(struct vnic_stats);

	return vnic_dev_cmd(vdev, CMD_STATS_DUMP, &a0, &a1, wait);
}