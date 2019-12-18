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
typedef  int /*<<< orphan*/  u16 ;
struct efx_rx_queue {unsigned int removed_count; unsigned int scatter_n; unsigned int ptr_mask; } ;
struct efx_nic {int /*<<< orphan*/  reset_pending; } ;
struct efx_channel {void* channel; int irq_mod_score; int /*<<< orphan*/  n_rx_mcast_mismatch; struct efx_nic* efx; } ;
typedef  int /*<<< orphan*/  efx_qword_t ;

/* Variables and functions */
 void* EFX_QWORD_FIELD (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFX_RX_PKT_CSUMMED ; 
 int /*<<< orphan*/  EFX_RX_PKT_DISCARD ; 
 int /*<<< orphan*/  EFX_RX_PKT_TCP ; 
#define  FSE_AZ_RX_EV_HDR_TYPE_OTHER 131 
#define  FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_OTHER 130 
#define  FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_TCP 129 
#define  FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_UDP 128 
 int /*<<< orphan*/  FSF_AZ_RX_EV_BYTE_CNT ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_DESC_PTR ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_HDR_TYPE ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_JUMBO_CONT ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_MCAST_HASH_MATCH ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_MCAST_PKT ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_PKT_OK ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_Q_LABEL ; 
 int /*<<< orphan*/  FSF_AZ_RX_EV_SOP ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct efx_rx_queue* efx_channel_get_rx_queue (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_farch_handle_rx_bad_index (struct efx_rx_queue*,unsigned int) ; 
 int /*<<< orphan*/  efx_farch_handle_rx_not_ok (struct efx_rx_queue*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  efx_rx_packet (struct efx_rx_queue*,int,int,unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
efx_farch_handle_rx_event(struct efx_channel *channel, const efx_qword_t *event)
{
	unsigned int rx_ev_desc_ptr, rx_ev_byte_cnt;
	unsigned int rx_ev_hdr_type, rx_ev_mcast_pkt;
	unsigned expected_ptr;
	bool rx_ev_pkt_ok, rx_ev_sop, rx_ev_cont;
	u16 flags;
	struct efx_rx_queue *rx_queue;
	struct efx_nic *efx = channel->efx;

	if (unlikely(READ_ONCE(efx->reset_pending)))
		return;

	rx_ev_cont = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_JUMBO_CONT);
	rx_ev_sop = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_SOP);
	WARN_ON(EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_Q_LABEL) !=
		channel->channel);

	rx_queue = efx_channel_get_rx_queue(channel);

	rx_ev_desc_ptr = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_DESC_PTR);
	expected_ptr = ((rx_queue->removed_count + rx_queue->scatter_n) &
			rx_queue->ptr_mask);

	/* Check for partial drops and other errors */
	if (unlikely(rx_ev_desc_ptr != expected_ptr) ||
	    unlikely(rx_ev_sop != (rx_queue->scatter_n == 0))) {
		if (rx_ev_desc_ptr != expected_ptr &&
		    !efx_farch_handle_rx_bad_index(rx_queue, rx_ev_desc_ptr))
			return;

		/* Discard all pending fragments */
		if (rx_queue->scatter_n) {
			efx_rx_packet(
				rx_queue,
				rx_queue->removed_count & rx_queue->ptr_mask,
				rx_queue->scatter_n, 0, EFX_RX_PKT_DISCARD);
			rx_queue->removed_count += rx_queue->scatter_n;
			rx_queue->scatter_n = 0;
		}

		/* Return if there is no new fragment */
		if (rx_ev_desc_ptr != expected_ptr)
			return;

		/* Discard new fragment if not SOP */
		if (!rx_ev_sop) {
			efx_rx_packet(
				rx_queue,
				rx_queue->removed_count & rx_queue->ptr_mask,
				1, 0, EFX_RX_PKT_DISCARD);
			++rx_queue->removed_count;
			return;
		}
	}

	++rx_queue->scatter_n;
	if (rx_ev_cont)
		return;

	rx_ev_byte_cnt = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_BYTE_CNT);
	rx_ev_pkt_ok = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_PKT_OK);
	rx_ev_hdr_type = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_HDR_TYPE);

	if (likely(rx_ev_pkt_ok)) {
		/* If packet is marked as OK then we can rely on the
		 * hardware checksum and classification.
		 */
		flags = 0;
		switch (rx_ev_hdr_type) {
		case FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_TCP:
			flags |= EFX_RX_PKT_TCP;
			/* fall through */
		case FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_UDP:
			flags |= EFX_RX_PKT_CSUMMED;
			/* fall through */
		case FSE_CZ_RX_EV_HDR_TYPE_IPV4V6_OTHER:
		case FSE_AZ_RX_EV_HDR_TYPE_OTHER:
			break;
		}
	} else {
		flags = efx_farch_handle_rx_not_ok(rx_queue, event);
	}

	/* Detect multicast packets that didn't match the filter */
	rx_ev_mcast_pkt = EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_MCAST_PKT);
	if (rx_ev_mcast_pkt) {
		unsigned int rx_ev_mcast_hash_match =
			EFX_QWORD_FIELD(*event, FSF_AZ_RX_EV_MCAST_HASH_MATCH);

		if (unlikely(!rx_ev_mcast_hash_match)) {
			++channel->n_rx_mcast_mismatch;
			flags |= EFX_RX_PKT_DISCARD;
		}
	}

	channel->irq_mod_score += 2;

	/* Handle received packet */
	efx_rx_packet(rx_queue,
		      rx_queue->removed_count & rx_queue->ptr_mask,
		      rx_queue->scatter_n, rx_ev_byte_cnt, flags);
	rx_queue->removed_count += rx_queue->scatter_n;
	rx_queue->scatter_n = 0;
}