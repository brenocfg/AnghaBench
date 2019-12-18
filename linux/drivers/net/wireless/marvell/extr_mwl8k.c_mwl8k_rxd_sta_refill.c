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
struct mwl8k_rxd_sta {scalar_t__ rx_ctrl; int /*<<< orphan*/  pkt_phys_addr; int /*<<< orphan*/  pkt_len; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mwl8k_rxd_sta_refill(void *_rxd, dma_addr_t addr, int len)
{
	struct mwl8k_rxd_sta *rxd = _rxd;

	rxd->pkt_len = cpu_to_le16(len);
	rxd->pkt_phys_addr = cpu_to_le32(addr);
	wmb();
	rxd->rx_ctrl = 0;
}