#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int rx_refill_thresh; int /*<<< orphan*/  rx_allocthresh; int /*<<< orphan*/  rx_alloc_thresh; int /*<<< orphan*/  tx_full; int /*<<< orphan*/  rx_refill; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx_comp_multi; } ;
struct htc_service_connect_req {int /*<<< orphan*/  svc_id; int /*<<< orphan*/  conn_flags; TYPE_1__ ep_cb; int /*<<< orphan*/  max_rxmsg_sz; int /*<<< orphan*/  flags; int /*<<< orphan*/  max_txq_depth; } ;
struct ath6kl {int dummy; } ;
typedef  int /*<<< orphan*/  connect ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_BUFFER_SIZE ; 
 int ATH6KL_MAX_RX_BUFFERS ; 
 int EIO ; 
 int /*<<< orphan*/  HTC_CONN_FLGS_REDUCE_CRED_DRIB ; 
 int /*<<< orphan*/  HTC_CONN_FLGS_THRESH_LVL_HALF ; 
 int /*<<< orphan*/  HTC_CONN_FLGS_THRESH_MASK ; 
 int /*<<< orphan*/  HTC_FLGS_TX_BNDL_PAD_EN ; 
 int /*<<< orphan*/  MAX_DEFAULT_SEND_QUEUE_DEPTH ; 
 int /*<<< orphan*/  WMI_CONTROL_SVC ; 
 int /*<<< orphan*/  WMI_DATA_BE_SVC ; 
 int /*<<< orphan*/  WMI_DATA_BK_SVC ; 
 int /*<<< orphan*/  WMI_DATA_VI_SVC ; 
 int /*<<< orphan*/  WMI_DATA_VO_SVC ; 
 int /*<<< orphan*/  WMI_MAX_TX_DATA_FRAME_LENGTH ; 
 int /*<<< orphan*/  ath6kl_alloc_amsdu_rxbuf ; 
 scalar_t__ ath6kl_connectservice (struct ath6kl*,struct htc_service_connect_req*,char*) ; 
 int /*<<< orphan*/  ath6kl_rx ; 
 int /*<<< orphan*/  ath6kl_rx_refill ; 
 int /*<<< orphan*/  ath6kl_tx_complete ; 
 int /*<<< orphan*/  ath6kl_tx_queue_full ; 
 int /*<<< orphan*/  memset (struct htc_service_connect_req*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath6kl_init_service_ep(struct ath6kl *ar)
{
	struct htc_service_connect_req connect;

	memset(&connect, 0, sizeof(connect));

	/* these fields are the same for all service endpoints */
	connect.ep_cb.tx_comp_multi = ath6kl_tx_complete;
	connect.ep_cb.rx = ath6kl_rx;
	connect.ep_cb.rx_refill = ath6kl_rx_refill;
	connect.ep_cb.tx_full = ath6kl_tx_queue_full;

	/*
	 * Set the max queue depth so that our ath6kl_tx_queue_full handler
	 * gets called.
	*/
	connect.max_txq_depth = MAX_DEFAULT_SEND_QUEUE_DEPTH;
	connect.ep_cb.rx_refill_thresh = ATH6KL_MAX_RX_BUFFERS / 4;
	if (!connect.ep_cb.rx_refill_thresh)
		connect.ep_cb.rx_refill_thresh++;

	/* connect to control service */
	connect.svc_id = WMI_CONTROL_SVC;
	if (ath6kl_connectservice(ar, &connect, "WMI CONTROL"))
		return -EIO;

	connect.flags |= HTC_FLGS_TX_BNDL_PAD_EN;

	/*
	 * Limit the HTC message size on the send path, although e can
	 * receive A-MSDU frames of 4K, we will only send ethernet-sized
	 * (802.3) frames on the send path.
	 */
	connect.max_rxmsg_sz = WMI_MAX_TX_DATA_FRAME_LENGTH;

	/*
	 * To reduce the amount of committed memory for larger A_MSDU
	 * frames, use the recv-alloc threshold mechanism for larger
	 * packets.
	 */
	connect.ep_cb.rx_alloc_thresh = ATH6KL_BUFFER_SIZE;
	connect.ep_cb.rx_allocthresh = ath6kl_alloc_amsdu_rxbuf;

	/*
	 * For the remaining data services set the connection flag to
	 * reduce dribbling, if configured to do so.
	 */
	connect.conn_flags |= HTC_CONN_FLGS_REDUCE_CRED_DRIB;
	connect.conn_flags &= ~HTC_CONN_FLGS_THRESH_MASK;
	connect.conn_flags |= HTC_CONN_FLGS_THRESH_LVL_HALF;

	connect.svc_id = WMI_DATA_BE_SVC;

	if (ath6kl_connectservice(ar, &connect, "WMI DATA BE"))
		return -EIO;

	/* connect to back-ground map this to WMI LOW_PRI */
	connect.svc_id = WMI_DATA_BK_SVC;
	if (ath6kl_connectservice(ar, &connect, "WMI DATA BK"))
		return -EIO;

	/* connect to Video service, map this to HI PRI */
	connect.svc_id = WMI_DATA_VI_SVC;
	if (ath6kl_connectservice(ar, &connect, "WMI DATA VI"))
		return -EIO;

	/*
	 * Connect to VO service, this is currently not mapped to a WMI
	 * priority stream due to historical reasons. WMI originally
	 * defined 3 priorities over 3 mailboxes We can change this when
	 * WMI is reworked so that priorities are not dependent on
	 * mailboxes.
	 */
	connect.svc_id = WMI_DATA_VO_SVC;
	if (ath6kl_connectservice(ar, &connect, "WMI DATA VO"))
		return -EIO;

	return 0;
}