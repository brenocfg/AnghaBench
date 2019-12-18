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
typedef  scalar_t__ u32 ;
struct xlgmac_pkt_info {int rx_tstamp; int /*<<< orphan*/  attributes; } ;
struct xlgmac_dma_desc {int /*<<< orphan*/  desc0; int /*<<< orphan*/  desc1; int /*<<< orphan*/  desc3; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CONTEXT_DESC3_TSA_LEN ; 
 int /*<<< orphan*/  RX_CONTEXT_DESC3_TSA_POS ; 
 int /*<<< orphan*/  RX_CONTEXT_DESC3_TSD_LEN ; 
 int /*<<< orphan*/  RX_CONTEXT_DESC3_TSD_POS ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RX_TSTAMP_LEN ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES_RX_TSTAMP_POS ; 
 scalar_t__ XLGMAC_GET_REG_BITS_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XLGMAC_SET_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xlgmac_get_rx_tstamp(struct xlgmac_pkt_info *pkt_info,
				 struct xlgmac_dma_desc *dma_desc)
{
	u32 tsa, tsd;
	u64 nsec;

	tsa = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_CONTEXT_DESC3_TSA_POS,
				RX_CONTEXT_DESC3_TSA_LEN);
	tsd = XLGMAC_GET_REG_BITS_LE(dma_desc->desc3,
				     RX_CONTEXT_DESC3_TSD_POS,
				RX_CONTEXT_DESC3_TSD_LEN);
	if (tsa && !tsd) {
		nsec = le32_to_cpu(dma_desc->desc1);
		nsec <<= 32;
		nsec |= le32_to_cpu(dma_desc->desc0);
		if (nsec != 0xffffffffffffffffULL) {
			pkt_info->rx_tstamp = nsec;
			pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_RX_TSTAMP_POS,
					RX_PACKET_ATTRIBUTES_RX_TSTAMP_LEN,
					1);
		}
	}
}