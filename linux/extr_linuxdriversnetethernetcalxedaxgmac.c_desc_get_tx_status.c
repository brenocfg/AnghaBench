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
struct xgmac_extra_stats {int /*<<< orphan*/  tx_payload_error; int /*<<< orphan*/  tx_remote_fault; int /*<<< orphan*/  tx_local_fault; int /*<<< orphan*/  tx_ip_header_error; int /*<<< orphan*/  tx_frame_flushed; int /*<<< orphan*/  tx_jabber; } ;
struct xgmac_priv {int /*<<< orphan*/  base; int /*<<< orphan*/  dev; struct xgmac_extra_stats xstats; } ;
struct xgmac_dma_desc {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int TXDESC_ERROR_SUMMARY ; 
 int TXDESC_FRAME_FLUSHED ; 
 int TXDESC_IP_HEADER_ERR ; 
 int TXDESC_JABBER_TIMEOUT ; 
 int TXDESC_LOCAL_FAULT ; 
 int TXDESC_PAYLOAD_CSUM_ERR ; 
 int TXDESC_REMOTE_FAULT ; 
 int TXDESC_UNDERFLOW_ERR ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  xgmac_dma_flush_tx_fifo (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int desc_get_tx_status(struct xgmac_priv *priv, struct xgmac_dma_desc *p)
{
	struct xgmac_extra_stats *x = &priv->xstats;
	u32 status = le32_to_cpu(p->flags);

	if (!(status & TXDESC_ERROR_SUMMARY))
		return 0;

	netdev_dbg(priv->dev, "tx desc error = 0x%08x\n", status);
	if (status & TXDESC_JABBER_TIMEOUT)
		x->tx_jabber++;
	if (status & TXDESC_FRAME_FLUSHED)
		x->tx_frame_flushed++;
	if (status & TXDESC_UNDERFLOW_ERR)
		xgmac_dma_flush_tx_fifo(priv->base);
	if (status & TXDESC_IP_HEADER_ERR)
		x->tx_ip_header_error++;
	if (status & TXDESC_LOCAL_FAULT)
		x->tx_local_fault++;
	if (status & TXDESC_REMOTE_FAULT)
		x->tx_remote_fault++;
	if (status & TXDESC_PAYLOAD_CSUM_ERR)
		x->tx_payload_error++;

	return -1;
}