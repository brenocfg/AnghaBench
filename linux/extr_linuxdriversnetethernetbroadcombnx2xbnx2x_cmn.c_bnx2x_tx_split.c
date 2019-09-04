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
typedef  size_t u16 ;
struct sw_tx_bd {int /*<<< orphan*/  flags; } ;
struct eth_tx_start_bd {void* addr_lo; void* addr_hi; void* nbytes; } ;
struct eth_tx_bd {void* addr_lo; void* addr_hi; void* nbytes; } ;
struct bnx2x_fp_txdata {TYPE_1__* tx_desc_ring; } ;
struct bnx2x {int dummy; } ;
typedef  size_t dma_addr_t ;
struct TYPE_2__ {struct eth_tx_bd reg_bd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_TSO_SPLIT_BD ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,void*,void*,void*) ; 
 size_t HILO_U64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETIF_MSG_TX_QUEUED ; 
 int /*<<< orphan*/  NEXT_TX_IDX (size_t) ; 
 size_t TX_BD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U64_HI (size_t) ; 
 int /*<<< orphan*/  U64_LO (size_t) ; 
 void* cpu_to_le16 (size_t) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int le16_to_cpu (void*) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 

__attribute__((used)) static u16 bnx2x_tx_split(struct bnx2x *bp,
			  struct bnx2x_fp_txdata *txdata,
			  struct sw_tx_bd *tx_buf,
			  struct eth_tx_start_bd **tx_bd, u16 hlen,
			  u16 bd_prod)
{
	struct eth_tx_start_bd *h_tx_bd = *tx_bd;
	struct eth_tx_bd *d_tx_bd;
	dma_addr_t mapping;
	int old_len = le16_to_cpu(h_tx_bd->nbytes);

	/* first fix first BD */
	h_tx_bd->nbytes = cpu_to_le16(hlen);

	DP(NETIF_MSG_TX_QUEUED,	"TSO split header size is %d (%x:%x)\n",
	   h_tx_bd->nbytes, h_tx_bd->addr_hi, h_tx_bd->addr_lo);

	/* now get a new data BD
	 * (after the pbd) and fill it */
	bd_prod = TX_BD(NEXT_TX_IDX(bd_prod));
	d_tx_bd = &txdata->tx_desc_ring[bd_prod].reg_bd;

	mapping = HILO_U64(le32_to_cpu(h_tx_bd->addr_hi),
			   le32_to_cpu(h_tx_bd->addr_lo)) + hlen;

	d_tx_bd->addr_hi = cpu_to_le32(U64_HI(mapping));
	d_tx_bd->addr_lo = cpu_to_le32(U64_LO(mapping));
	d_tx_bd->nbytes = cpu_to_le16(old_len - hlen);

	/* this marks the BD as one that has no individual mapping */
	tx_buf->flags |= BNX2X_TSO_SPLIT_BD;

	DP(NETIF_MSG_TX_QUEUED,
	   "TSO split data size is %d (%x:%x)\n",
	   d_tx_bd->nbytes, d_tx_bd->addr_hi, d_tx_bd->addr_lo);

	/* update tx_bd */
	*tx_bd = (struct eth_tx_start_bd *)d_tx_bd;

	return bd_prod;
}