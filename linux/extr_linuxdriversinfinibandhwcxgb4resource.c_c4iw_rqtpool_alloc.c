#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {scalar_t__ cur; scalar_t__ max; int /*<<< orphan*/  fail; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ rqt; } ;
struct TYPE_4__ {int /*<<< orphan*/  pdev; } ;
struct c4iw_rdev {TYPE_3__ stats; int /*<<< orphan*/  rqt_kref; TYPE_1__ lldi; int /*<<< orphan*/  rqt_pool; } ;

/* Variables and functions */
 int MIN_RQT_SHIFT ; 
 unsigned long gen_pool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ roundup (int,int) ; 

u32 c4iw_rqtpool_alloc(struct c4iw_rdev *rdev, int size)
{
	unsigned long addr = gen_pool_alloc(rdev->rqt_pool, size << 6);
	pr_debug("addr 0x%x size %d\n", (u32)addr, size << 6);
	if (!addr)
		pr_warn_ratelimited("%s: Out of RQT memory\n",
				    pci_name(rdev->lldi.pdev));
	mutex_lock(&rdev->stats.lock);
	if (addr) {
		rdev->stats.rqt.cur += roundup(size << 6, 1 << MIN_RQT_SHIFT);
		if (rdev->stats.rqt.cur > rdev->stats.rqt.max)
			rdev->stats.rqt.max = rdev->stats.rqt.cur;
		kref_get(&rdev->rqt_kref);
	} else
		rdev->stats.rqt.fail++;
	mutex_unlock(&rdev->stats.lock);
	return (u32)addr;
}