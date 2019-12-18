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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct netsec_priv {int dummy; } ;

/* Variables and functions */
 int NETSEC_XDP_REDIR ; 
 int NETSEC_XDP_TX ; 
 int /*<<< orphan*/  netsec_xdp_ring_tx_db (struct netsec_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdp_do_flush_map () ; 

__attribute__((used)) static void netsec_finalize_xdp_rx(struct netsec_priv *priv, u32 xdp_res,
				   u16 pkts)
{
	if (xdp_res & NETSEC_XDP_REDIR)
		xdp_do_flush_map();

	if (xdp_res & NETSEC_XDP_TX)
		netsec_xdp_ring_tx_db(priv, pkts);
}