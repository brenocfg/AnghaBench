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
struct velocity_info_tbl {int /*<<< orphan*/  txqueue; int /*<<< orphan*/  chip_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  numq; } ;
struct velocity_info {int /*<<< orphan*/  lock; int /*<<< orphan*/  multicast_limit; TYPE_1__ tx; int /*<<< orphan*/  chip_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCAM_SIZE ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void velocity_init_info(struct velocity_info *vptr,
				const struct velocity_info_tbl *info)
{
	vptr->chip_id = info->chip_id;
	vptr->tx.numq = info->txqueue;
	vptr->multicast_limit = MCAM_SIZE;
	spin_lock_init(&vptr->lock);
}