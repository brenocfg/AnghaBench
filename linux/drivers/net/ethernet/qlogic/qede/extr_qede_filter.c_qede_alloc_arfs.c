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
struct TYPE_4__ {struct TYPE_4__* arfs_fltr_bmap; int /*<<< orphan*/  arfs_list_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  rx_cpu_rmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDE_ARFS_BUCKET_HEAD (struct qede_dev*,int) ; 
 int QEDE_RFS_FLW_MASK ; 
 int /*<<< orphan*/  QEDE_RFS_MAX_FLTR ; 
 int /*<<< orphan*/  QEDE_RSS_COUNT (struct qede_dev*) ; 
 int /*<<< orphan*/  alloc_irq_cpu_rmap (int /*<<< orphan*/ ) ; 
 int array_size (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (TYPE_2__*) ; 
 void* vzalloc (int) ; 

int qede_alloc_arfs(struct qede_dev *edev)
{
	int i;

	edev->arfs = vzalloc(sizeof(*edev->arfs));
	if (!edev->arfs)
		return -ENOMEM;

	spin_lock_init(&edev->arfs->arfs_list_lock);

	for (i = 0; i <= QEDE_RFS_FLW_MASK; i++)
		INIT_HLIST_HEAD(QEDE_ARFS_BUCKET_HEAD(edev, i));

	edev->arfs->arfs_fltr_bmap =
		vzalloc(array_size(sizeof(long),
				   BITS_TO_LONGS(QEDE_RFS_MAX_FLTR)));
	if (!edev->arfs->arfs_fltr_bmap) {
		vfree(edev->arfs);
		edev->arfs = NULL;
		return -ENOMEM;
	}

#ifdef CONFIG_RFS_ACCEL
	edev->ndev->rx_cpu_rmap = alloc_irq_cpu_rmap(QEDE_RSS_COUNT(edev));
	if (!edev->ndev->rx_cpu_rmap) {
		vfree(edev->arfs->arfs_fltr_bmap);
		edev->arfs->arfs_fltr_bmap = NULL;
		vfree(edev->arfs);
		edev->arfs = NULL;
		return -ENOMEM;
	}
#endif
	return 0;
}