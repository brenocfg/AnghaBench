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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct bnxt_tx_ring_info {int dummy; } ;
struct bnxt_sw_tx_bd {int /*<<< orphan*/  action; int /*<<< orphan*/  rx_prod; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  XDP_TX ; 
 struct bnxt_sw_tx_bd* bnxt_xmit_bd (struct bnxt*,struct bnxt_tx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bnxt_xmit_xdp(struct bnxt *bp, struct bnxt_tx_ring_info *txr,
			    dma_addr_t mapping, u32 len, u16 rx_prod)
{
	struct bnxt_sw_tx_bd *tx_buf;

	tx_buf = bnxt_xmit_bd(bp, txr, mapping, len);
	tx_buf->rx_prod = rx_prod;
	tx_buf->action = XDP_TX;
}