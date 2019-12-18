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
struct bnx2_napi {int dummy; } ;
struct bnx2 {int /*<<< orphan*/  phy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  STATUS_ATTN_BITS_LINK_STATE ; 
 int /*<<< orphan*/  STATUS_ATTN_BITS_TIMER_ABORT ; 
 scalar_t__ bnx2_phy_event_is_set (struct bnx2*,struct bnx2_napi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2_set_link (struct bnx2*) ; 
 int /*<<< orphan*/  bnx2_set_remote_link (struct bnx2*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2_phy_int(struct bnx2 *bp, struct bnx2_napi *bnapi)
{
	spin_lock(&bp->phy_lock);

	if (bnx2_phy_event_is_set(bp, bnapi, STATUS_ATTN_BITS_LINK_STATE))
		bnx2_set_link(bp);
	if (bnx2_phy_event_is_set(bp, bnapi, STATUS_ATTN_BITS_TIMER_ABORT))
		bnx2_set_remote_link(bp);

	spin_unlock(&bp->phy_lock);

}