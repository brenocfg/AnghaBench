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
struct xdp_frame {int dummy; } ;
struct bnxt_tx_ring_info {int dummy; } ;
struct bnxt_sw_tx_bd {struct xdp_frame* xdpf; int /*<<< orphan*/  action; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  XDP_REDIRECT ; 
 struct bnxt_sw_tx_bd* bnxt_xmit_bd (struct bnxt*,struct bnxt_tx_ring_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_len_set (struct bnxt_sw_tx_bd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __bnxt_xmit_xdp_redirect(struct bnxt *bp,
				     struct bnxt_tx_ring_info *txr,
				     dma_addr_t mapping, u32 len,
				     struct xdp_frame *xdpf)
{
	struct bnxt_sw_tx_bd *tx_buf;

	tx_buf = bnxt_xmit_bd(bp, txr, mapping, len);
	tx_buf->action = XDP_REDIRECT;
	tx_buf->xdpf = xdpf;
	dma_unmap_addr_set(tx_buf, mapping, mapping);
	dma_unmap_len_set(tx_buf, len, 0);
}