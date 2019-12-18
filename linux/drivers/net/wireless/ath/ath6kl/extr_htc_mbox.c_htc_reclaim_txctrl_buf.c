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
struct htc_target {int /*<<< orphan*/  htc_lock; int /*<<< orphan*/  free_ctrl_txbuf; } ;
struct htc_packet {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htc_reclaim_txctrl_buf(struct htc_target *target,
				   struct htc_packet *pkt)
{
	spin_lock_bh(&target->htc_lock);
	list_add_tail(&pkt->list, &target->free_ctrl_txbuf);
	spin_unlock_bh(&target->htc_lock);
}