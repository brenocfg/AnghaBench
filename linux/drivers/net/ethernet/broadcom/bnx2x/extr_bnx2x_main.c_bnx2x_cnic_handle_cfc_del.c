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
struct TYPE_3__ {int /*<<< orphan*/  error; } ;
union event_ring_elem {TYPE_1__ message; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {scalar_t__ starting_cid; scalar_t__ iscsi_l2_cid; } ;
struct bnx2x {TYPE_2__ cnic_eth_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  BNX2X_MSG_SP ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  bnx2x_cnic_cfc_comp (struct bnx2x*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_panic_dump (struct bnx2x*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int  bnx2x_cnic_handle_cfc_del(struct bnx2x *bp, u32 cid,
				      union event_ring_elem *elem)
{
	u8 err = elem->message.error;

	if (!bp->cnic_eth_dev.starting_cid  ||
	    (cid < bp->cnic_eth_dev.starting_cid &&
	    cid != bp->cnic_eth_dev.iscsi_l2_cid))
		return 1;

	DP(BNX2X_MSG_SP, "got delete ramrod for CNIC CID %d\n", cid);

	if (unlikely(err)) {

		BNX2X_ERR("got delete ramrod for CNIC CID %d with error!\n",
			  cid);
		bnx2x_panic_dump(bp, false);
	}
	bnx2x_cnic_cfc_comp(bp, cid, err);
	return 0;
}