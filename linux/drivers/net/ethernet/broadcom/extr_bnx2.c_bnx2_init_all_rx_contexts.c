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
typedef  scalar_t__ u32 ;
struct bnx2 {int num_rx_rings; } ;

/* Variables and functions */
 scalar_t__ RX_CID ; 
 scalar_t__ RX_RSS_CID ; 
 int /*<<< orphan*/  bnx2_init_rx_context (struct bnx2*,scalar_t__) ; 

__attribute__((used)) static void
bnx2_init_all_rx_contexts(struct bnx2 *bp)
{
	int i;
	u32 cid;

	for (i = 0, cid = RX_CID; i < bp->num_rx_rings; i++, cid++) {
		if (i == 1)
			cid = RX_RSS_CID;
		bnx2_init_rx_context(bp, cid);
	}
}