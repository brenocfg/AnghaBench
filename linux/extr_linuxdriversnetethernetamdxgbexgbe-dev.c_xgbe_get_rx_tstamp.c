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
struct xgbe_ring_desc {int /*<<< orphan*/  desc0; int /*<<< orphan*/  desc1; int /*<<< orphan*/  desc3; } ;
struct xgbe_packet_data {int rx_tstamp; int /*<<< orphan*/  attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_CONTEXT_DESC3 ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES ; 
 int /*<<< orphan*/  RX_TSTAMP ; 
 int /*<<< orphan*/  TSA ; 
 int /*<<< orphan*/  TSD ; 
 scalar_t__ XGMAC_GET_BITS_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgbe_get_rx_tstamp(struct xgbe_packet_data *packet,
			       struct xgbe_ring_desc *rdesc)
{
	u64 nsec;

	if (XGMAC_GET_BITS_LE(rdesc->desc3, RX_CONTEXT_DESC3, TSA) &&
	    !XGMAC_GET_BITS_LE(rdesc->desc3, RX_CONTEXT_DESC3, TSD)) {
		nsec = le32_to_cpu(rdesc->desc1);
		nsec <<= 32;
		nsec |= le32_to_cpu(rdesc->desc0);
		if (nsec != 0xffffffffffffffffULL) {
			packet->rx_tstamp = nsec;
			XGMAC_SET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES,
				       RX_TSTAMP, 1);
		}
	}
}