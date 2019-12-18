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
typedef  int u64 ;
struct niu {scalar_t__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_LOG_MASK1 (int) ; 
 int /*<<< orphan*/  TX_LOG_MASK2 (int) ; 
 int /*<<< orphan*/  TX_LOG_PAGE_HDL (int) ; 
 int /*<<< orphan*/  TX_LOG_PAGE_RELO1 (int) ; 
 int /*<<< orphan*/  TX_LOG_PAGE_RELO2 (int) ; 
 int /*<<< orphan*/  TX_LOG_PAGE_VLD (int) ; 
 int TX_LOG_PAGE_VLD_FUNC_SHIFT ; 
 int TX_LOG_PAGE_VLD_PAGE0 ; 
 int TX_LOG_PAGE_VLD_PAGE1 ; 
 int /*<<< orphan*/  TX_LOG_VAL1 (int) ; 
 int /*<<< orphan*/  TX_LOG_VAL2 (int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_tx_channel_lpage_init(struct niu *np, int channel)
{
	u64 val;

	nw64(TX_LOG_MASK1(channel), 0);
	nw64(TX_LOG_VAL1(channel), 0);
	nw64(TX_LOG_MASK2(channel), 0);
	nw64(TX_LOG_VAL2(channel), 0);
	nw64(TX_LOG_PAGE_RELO1(channel), 0);
	nw64(TX_LOG_PAGE_RELO2(channel), 0);
	nw64(TX_LOG_PAGE_HDL(channel), 0);

	val  = (u64)np->port << TX_LOG_PAGE_VLD_FUNC_SHIFT;
	val |= (TX_LOG_PAGE_VLD_PAGE0 | TX_LOG_PAGE_VLD_PAGE1);
	nw64(TX_LOG_PAGE_VLD(channel), val);

	/* XXX TXDMA 32bit mode? XXX */

	return 0;
}