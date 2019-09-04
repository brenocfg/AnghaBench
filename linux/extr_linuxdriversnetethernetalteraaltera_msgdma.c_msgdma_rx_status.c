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
struct altera_tse_private {int /*<<< orphan*/  rx_dma_resp; int /*<<< orphan*/  rx_dma_csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bytes_transferred ; 
 int csrrd32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgdma_csroffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgdma_respoffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resp_fill_level ; 
 int /*<<< orphan*/  status ; 

u32 msgdma_rx_status(struct altera_tse_private *priv)
{
	u32 rxstatus = 0;
	u32 pktlength;
	u32 pktstatus;

	if (csrrd32(priv->rx_dma_csr, msgdma_csroffs(resp_fill_level))
	    & 0xffff) {
		pktlength = csrrd32(priv->rx_dma_resp,
				    msgdma_respoffs(bytes_transferred));
		pktstatus = csrrd32(priv->rx_dma_resp,
				    msgdma_respoffs(status));
		rxstatus = pktstatus;
		rxstatus = rxstatus << 16;
		rxstatus |= (pktlength & 0xffff);
	}
	return rxstatus;
}