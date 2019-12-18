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
struct qede_dev {TYPE_2__* arfs; TYPE_1__* ndev; } ;
struct TYPE_4__ {struct TYPE_4__* arfs_fltr_bmap; } ;
struct TYPE_3__ {int /*<<< orphan*/ * rx_cpu_rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq_cpu_rmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 

void qede_free_arfs(struct qede_dev *edev)
{
	if (!edev->arfs)
		return;

#ifdef CONFIG_RFS_ACCEL
	if (edev->ndev->rx_cpu_rmap)
		free_irq_cpu_rmap(edev->ndev->rx_cpu_rmap);

	edev->ndev->rx_cpu_rmap = NULL;
#endif
	vfree(edev->arfs->arfs_fltr_bmap);
	edev->arfs->arfs_fltr_bmap = NULL;
	vfree(edev->arfs);
	edev->arfs = NULL;
}