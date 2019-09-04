#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int dma_len; } ;
struct TYPE_4__ {unsigned int len; TYPE_1__ buf; } ;
struct xgbe_ring_data {TYPE_2__ rx; } ;
struct xgbe_packet_data {int /*<<< orphan*/  attributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAST ; 
 int /*<<< orphan*/  RX_PACKET_ATTRIBUTES ; 
 int /*<<< orphan*/  XGMAC_GET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int xgbe_rx_buf2_len(struct xgbe_ring_data *rdata,
				     struct xgbe_packet_data *packet,
				     unsigned int len)
{
	/* Always the full buffer if not the last descriptor */
	if (!XGMAC_GET_BITS(packet->attributes, RX_PACKET_ATTRIBUTES, LAST))
		return rdata->rx.buf.dma_len;

	/* Last descriptor so calculate how much of the buffer was used
	 * for the last bit of data
	 */
	return rdata->rx.len - len;
}