#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct TYPE_5__ {int is_hold_timer_set; scalar_t__ hold_tmo_msecs; int /*<<< orphan*/  hold_timer; } ;
struct TYPE_6__ {scalar_t__ aggr_len; scalar_t__ aggr_num; TYPE_2__ timer_cnxt; int /*<<< orphan*/  aggr_list; } ;
struct usb_tx_data_port {scalar_t__ tx_data_ix; int block_status; TYPE_3__ tx_aggr; struct urb_context* tx_data_list; int /*<<< orphan*/  tx_data_urb_pending; } ;
struct urb_context {int dummy; } ;
struct txpd {int flags; } ;
struct sk_buff {int* data; int len; } ;
struct mwifiex_tx_param {scalar_t__ next_pkt_len; } ;
struct TYPE_4__ {int tx_aggr_align; scalar_t__ tx_aggr_max_size; scalar_t__ tx_aggr_max_num; } ;
struct mwifiex_adapter {int intf_hdr_len; int /*<<< orphan*/  data_sent; TYPE_1__ bus_aggr; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 scalar_t__ MWIFIEX_TX_DATA_URB ; 
 int MWIFIEX_TYPE_AGGR_DATA_V2 ; 
 int MWIFIEX_TxPD_POWER_MGMT_NULL_PACKET ; 
 scalar_t__ MWIFIEX_USB_TX_AGGR_TMO_MAX ; 
 void* MWIFIEX_USB_TX_AGGR_TMO_MIN ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int cpu_to_le16 (int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (scalar_t__) ; 
 int mwifiex_usb_construct_send_urb (struct mwifiex_adapter*,struct usb_tx_data_port*,int,struct urb_context*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_usb_data_sent (struct mwifiex_adapter*) ; 
 int mwifiex_usb_prepare_tx_aggr_skb (struct mwifiex_adapter*,struct usb_tx_data_port*,struct sk_buff**) ; 
 int /*<<< orphan*/  mwifiex_write_data_complete (struct mwifiex_adapter*,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int mwifiex_usb_aggr_tx_data(struct mwifiex_adapter *adapter, u8 ep,
				    struct sk_buff *skb,
				    struct mwifiex_tx_param *tx_param,
				    struct usb_tx_data_port *port)
{
	u8 *payload, pad;
	u16 align = adapter->bus_aggr.tx_aggr_align;
	struct sk_buff *skb_send = NULL;
	struct urb_context *context = NULL;
	struct txpd *local_tx_pd =
		(struct txpd *)((u8 *)skb->data + adapter->intf_hdr_len);
	u8 f_send_aggr_buf = 0;
	u8 f_send_cur_buf = 0;
	u8 f_precopy_cur_buf = 0;
	u8 f_postcopy_cur_buf = 0;
	u32 timeout;
	int ret;

	/* padding to ensure each packet alginment */
	pad = (align - (skb->len & (align - 1))) % align;

	if (tx_param && tx_param->next_pkt_len) {
		/* next packet available in tx queue*/
		if (port->tx_aggr.aggr_len + skb->len + pad >
		    adapter->bus_aggr.tx_aggr_max_size) {
			f_send_aggr_buf = 1;
			f_postcopy_cur_buf = 1;
		} else {
			/* current packet could be aggregated*/
			f_precopy_cur_buf = 1;

			if (port->tx_aggr.aggr_len + skb->len + pad +
			    tx_param->next_pkt_len >
			    adapter->bus_aggr.tx_aggr_max_size ||
			    port->tx_aggr.aggr_num + 2 >
			    adapter->bus_aggr.tx_aggr_max_num) {
			    /* next packet could not be aggregated
			     * send current aggregation buffer
			     */
				f_send_aggr_buf = 1;
			}
		}
	} else {
		/* last packet in tx queue */
		if (port->tx_aggr.aggr_num > 0) {
			/* pending packets in aggregation buffer*/
			if (port->tx_aggr.aggr_len + skb->len + pad >
			    adapter->bus_aggr.tx_aggr_max_size) {
				/* current packet not be able to aggregated,
				 * send aggr buffer first, then send packet.
				 */
				f_send_cur_buf = 1;
			} else {
				/* last packet, Aggregation and send */
				f_precopy_cur_buf = 1;
			}

			f_send_aggr_buf = 1;
		} else {
			/* no pending packets in aggregation buffer,
			 * send current packet immediately
			 */
			 f_send_cur_buf = 1;
		}
	}

	if (local_tx_pd->flags & MWIFIEX_TxPD_POWER_MGMT_NULL_PACKET) {
		/* Send NULL packet immediately*/
		if (f_precopy_cur_buf) {
			if (skb_queue_empty(&port->tx_aggr.aggr_list)) {
				f_precopy_cur_buf = 0;
				f_send_aggr_buf = 0;
				f_send_cur_buf = 1;
			} else {
				f_send_aggr_buf = 1;
			}
		} else if (f_postcopy_cur_buf) {
			f_send_cur_buf = 1;
			f_postcopy_cur_buf = 0;
		}
	}

	if (f_precopy_cur_buf) {
		skb_queue_tail(&port->tx_aggr.aggr_list, skb);
		port->tx_aggr.aggr_len += (skb->len + pad);
		port->tx_aggr.aggr_num++;
		if (f_send_aggr_buf)
			goto send_aggr_buf;

		/* packet will not been send immediately,
		 * set a timer to make sure it will be sent under
		 * strict time limit. Dynamically fit the timeout
		 * value, according to packets number in aggr_list
		 */
		if (!port->tx_aggr.timer_cnxt.is_hold_timer_set) {
			port->tx_aggr.timer_cnxt.hold_tmo_msecs =
					MWIFIEX_USB_TX_AGGR_TMO_MIN;
			timeout =
				port->tx_aggr.timer_cnxt.hold_tmo_msecs;
			mod_timer(&port->tx_aggr.timer_cnxt.hold_timer,
				  jiffies + msecs_to_jiffies(timeout));
			port->tx_aggr.timer_cnxt.is_hold_timer_set = true;
		} else {
			if (port->tx_aggr.timer_cnxt.hold_tmo_msecs <
			    MWIFIEX_USB_TX_AGGR_TMO_MAX) {
				/* Dyanmic fit timeout */
				timeout =
				++port->tx_aggr.timer_cnxt.hold_tmo_msecs;
				mod_timer(&port->tx_aggr.timer_cnxt.hold_timer,
					  jiffies + msecs_to_jiffies(timeout));
			}
		}
	}

send_aggr_buf:
	if (f_send_aggr_buf) {
		ret = mwifiex_usb_prepare_tx_aggr_skb(adapter, port, &skb_send);
		if (!ret) {
			context = &port->tx_data_list[port->tx_data_ix++];
			ret = mwifiex_usb_construct_send_urb(adapter, port, ep,
							     context, skb_send);
			if (ret == -1)
				mwifiex_write_data_complete(adapter, skb_send,
							    0, -1);
		}
	}

	if (f_send_cur_buf) {
		if (f_send_aggr_buf) {
			if (atomic_read(&port->tx_data_urb_pending) >=
			    MWIFIEX_TX_DATA_URB) {
				port->block_status = true;
				adapter->data_sent =
					mwifiex_usb_data_sent(adapter);
				/* no available urb, postcopy packet*/
				f_postcopy_cur_buf = 1;
				goto postcopy_cur_buf;
			}

			if (port->tx_data_ix >= MWIFIEX_TX_DATA_URB)
				port->tx_data_ix = 0;
		}

		payload = skb->data;
		*(u16 *)&payload[2] =
			cpu_to_le16(MWIFIEX_TYPE_AGGR_DATA_V2 | 0x80);
		*(u16 *)payload = cpu_to_le16(skb->len);
		skb_send = skb;
		context = &port->tx_data_list[port->tx_data_ix++];
		return mwifiex_usb_construct_send_urb(adapter, port, ep,
						      context, skb_send);
	}

postcopy_cur_buf:
	if (f_postcopy_cur_buf) {
		skb_queue_tail(&port->tx_aggr.aggr_list, skb);
		port->tx_aggr.aggr_len += (skb->len + pad);
		port->tx_aggr.aggr_num++;
		/* New aggregation begin, start timer */
		if (!port->tx_aggr.timer_cnxt.is_hold_timer_set) {
			port->tx_aggr.timer_cnxt.hold_tmo_msecs =
					MWIFIEX_USB_TX_AGGR_TMO_MIN;
			timeout = port->tx_aggr.timer_cnxt.hold_tmo_msecs;
			mod_timer(&port->tx_aggr.timer_cnxt.hold_timer,
				  jiffies + msecs_to_jiffies(timeout));
			port->tx_aggr.timer_cnxt.is_hold_timer_set = true;
		}
	}

	return -EINPROGRESS;
}