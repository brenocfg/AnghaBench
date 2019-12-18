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
struct xgmac_extra_stats {int /*<<< orphan*/  rx_payload_error; int /*<<< orphan*/  rx_ip_header_error; int /*<<< orphan*/  rx_da_filter_fail; } ;
struct xgmac_priv {int /*<<< orphan*/  dev; struct xgmac_extra_stats xstats; } ;
struct xgmac_dma_desc {int /*<<< orphan*/  ext_status; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int CHECKSUM_NONE ; 
 int CHECKSUM_UNNECESSARY ; 
 int RXDESC_CRC_ERR ; 
 int RXDESC_DA_FILTER_FAIL ; 
 int RXDESC_DESCRIPTOR_ERR ; 
 int RXDESC_ERROR_SUMMARY ; 
 int RXDESC_EXT_STATUS ; 
 int RXDESC_FIRST_SEG ; 
 int RXDESC_FRAME_TYPE ; 
 int RXDESC_GIANT_FRAME ; 
 int RXDESC_IP_HEADER_ERR ; 
 int RXDESC_IP_PAYLOAD_ERR ; 
 int RXDESC_IP_PAYLOAD_MASK ; 
 int RXDESC_LAST_SEG ; 
 int RXDESC_LENGTH_ERR ; 
 int RXDESC_OVERFLOW_ERR ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int desc_get_rx_status(struct xgmac_priv *priv, struct xgmac_dma_desc *p)
{
	struct xgmac_extra_stats *x = &priv->xstats;
	int ret = CHECKSUM_UNNECESSARY;
	u32 status = le32_to_cpu(p->flags);
	u32 ext_status = le32_to_cpu(p->ext_status);

	if (status & RXDESC_DA_FILTER_FAIL) {
		netdev_dbg(priv->dev, "XGMAC RX : Dest Address filter fail\n");
		x->rx_da_filter_fail++;
		return -1;
	}

	/* All frames should fit into a single buffer */
	if (!(status & RXDESC_FIRST_SEG) || !(status & RXDESC_LAST_SEG))
		return -1;

	/* Check if packet has checksum already */
	if ((status & RXDESC_FRAME_TYPE) && (status & RXDESC_EXT_STATUS) &&
		!(ext_status & RXDESC_IP_PAYLOAD_MASK))
		ret = CHECKSUM_NONE;

	netdev_dbg(priv->dev, "rx status - frame type=%d, csum = %d, ext stat %08x\n",
		   (status & RXDESC_FRAME_TYPE) ? 1 : 0, ret, ext_status);

	if (!(status & RXDESC_ERROR_SUMMARY))
		return ret;

	/* Handle any errors */
	if (status & (RXDESC_DESCRIPTOR_ERR | RXDESC_OVERFLOW_ERR |
		RXDESC_GIANT_FRAME | RXDESC_LENGTH_ERR | RXDESC_CRC_ERR))
		return -1;

	if (status & RXDESC_EXT_STATUS) {
		if (ext_status & RXDESC_IP_HEADER_ERR)
			x->rx_ip_header_error++;
		if (ext_status & RXDESC_IP_PAYLOAD_ERR)
			x->rx_payload_error++;
		netdev_dbg(priv->dev, "IP checksum error - stat %08x\n",
			   ext_status);
		return CHECKSUM_NONE;
	}

	return ret;
}