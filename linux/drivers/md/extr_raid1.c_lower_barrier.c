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
struct r1conf {int /*<<< orphan*/  wait_barrier; int /*<<< orphan*/  nr_sync_pending; int /*<<< orphan*/ * barrier; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int sector_to_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void lower_barrier(struct r1conf *conf, sector_t sector_nr)
{
	int idx = sector_to_idx(sector_nr);

	BUG_ON(atomic_read(&conf->barrier[idx]) <= 0);

	atomic_dec(&conf->barrier[idx]);
	atomic_dec(&conf->nr_sync_pending);
	wake_up(&conf->wait_barrier);
}