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
struct bnx2x {TYPE_1__* fp; int /*<<< orphan*/  rx_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  cl_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_RX_MODE_FCOE_ETH ; 
 int /*<<< orphan*/  NO_FCOE (struct bnx2x*) ; 
 int /*<<< orphan*/  RAMROD_RX ; 
 int /*<<< orphan*/  RAMROD_TX ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int bnx2x_fill_accept_flags (struct bnx2x*,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 int bnx2x_set_q_rx_mode (struct bnx2x*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int bnx2x_set_storm_rx_mode(struct bnx2x *bp)
{
	unsigned long rx_mode_flags = 0, ramrod_flags = 0;
	unsigned long rx_accept_flags = 0, tx_accept_flags = 0;
	int rc;

	if (!NO_FCOE(bp))
		/* Configure rx_mode of FCoE Queue */
		__set_bit(BNX2X_RX_MODE_FCOE_ETH, &rx_mode_flags);

	rc = bnx2x_fill_accept_flags(bp, bp->rx_mode, &rx_accept_flags,
				     &tx_accept_flags);
	if (rc)
		return rc;

	__set_bit(RAMROD_RX, &ramrod_flags);
	__set_bit(RAMROD_TX, &ramrod_flags);

	return bnx2x_set_q_rx_mode(bp, bp->fp->cl_id, rx_mode_flags,
				   rx_accept_flags, tx_accept_flags,
				   ramrod_flags);
}