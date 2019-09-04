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
struct xen_blkif_ring {int /*<<< orphan*/  persistent_gnt_in_use; } ;
struct persistent_gnt {int active; int /*<<< orphan*/  last_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_alert_ratelimited (char*) ; 

__attribute__((used)) static void put_persistent_gnt(struct xen_blkif_ring *ring,
                               struct persistent_gnt *persistent_gnt)
{
	if (!persistent_gnt->active)
		pr_alert_ratelimited("freeing a grant already unused\n");
	persistent_gnt->last_used = jiffies;
	persistent_gnt->active = false;
	atomic_dec(&ring->persistent_gnt_in_use);
}