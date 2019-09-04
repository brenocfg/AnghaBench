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
struct TYPE_4__ {scalar_t__ toclean; int /*<<< orphan*/  max; int /*<<< orphan*/  free; int /*<<< orphan*/ * ht_head; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_arfs; } ;
struct enic {TYPE_2__ rfs_h; TYPE_1__ config; } ;

/* Variables and functions */
 int ENIC_RFS_FLW_MASK ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void enic_rfs_flw_tbl_init(struct enic *enic)
{
	int i;

	spin_lock_init(&enic->rfs_h.lock);
	for (i = 0; i <= ENIC_RFS_FLW_MASK; i++)
		INIT_HLIST_HEAD(&enic->rfs_h.ht_head[i]);
	enic->rfs_h.max = enic->config.num_arfs;
	enic->rfs_h.free = enic->rfs_h.max;
	enic->rfs_h.toclean = 0;
}