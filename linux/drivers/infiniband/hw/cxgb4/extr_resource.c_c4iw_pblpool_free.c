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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  cur; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; TYPE_1__ pbl; } ;
struct c4iw_rdev {int /*<<< orphan*/  pbl_kref; int /*<<< orphan*/  pbl_pool; TYPE_2__ stats; } ;

/* Variables and functions */
 int MIN_PBL_SHIFT ; 
 int /*<<< orphan*/  destroy_pblpool ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__,int) ; 
 scalar_t__ roundup (int,int) ; 

void c4iw_pblpool_free(struct c4iw_rdev *rdev, u32 addr, int size)
{
	pr_debug("addr 0x%x size %d\n", addr, size);
	mutex_lock(&rdev->stats.lock);
	rdev->stats.pbl.cur -= roundup(size, 1 << MIN_PBL_SHIFT);
	mutex_unlock(&rdev->stats.lock);
	gen_pool_free(rdev->pbl_pool, (unsigned long)addr, size);
	kref_put(&rdev->pbl_kref, destroy_pblpool);
}