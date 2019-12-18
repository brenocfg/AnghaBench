#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct list_head {int dummy; } ;
struct htc_target {int tx_bndl_mask; TYPE_4__* dev; int /*<<< orphan*/  msg_per_bndl_max; } ;
struct htc_packet {int /*<<< orphan*/  act_len; int /*<<< orphan*/  buf; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  status; } ;
struct htc_endpoint {scalar_t__ svc_id; size_t eid; struct htc_target* target; } ;
struct hif_scatter_req {scalar_t__ scat_q_depth; int scat_entries; TYPE_1__* scat_list; int /*<<< orphan*/  len; int /*<<< orphan*/  complete; } ;
struct TYPE_7__ {TYPE_2__* ar; } ;
struct TYPE_6__ {int* ep2ac_map; } ;
struct TYPE_5__ {struct htc_packet* packet; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH6KL_DBG_HTC ; 
 scalar_t__ ATH6KL_SCATTER_REQS ; 
 int EAGAIN ; 
 scalar_t__ HTC_CTRL_RSVD_SVC ; 
 int HTC_MIN_HTC_MSGS_TO_BUNDLE ; 
 scalar_t__ WMI_CONTROL_SVC ; 
 int WMM_AC_BE ; 
 int WMM_AC_BK ; 
 int WMM_NUM_AC ; 
 int /*<<< orphan*/  ath6kl_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ath6kl_hif_submit_scat_req (TYPE_4__*,struct hif_scatter_req*,int) ; 
 int ath6kl_htc_tx_setup_scat_list (struct htc_target*,struct htc_endpoint*,struct hif_scatter_req*,int,struct list_head*) ; 
 int get_queue_depth (struct list_head*) ; 
 int /*<<< orphan*/  hif_scatter_req_add (TYPE_2__*,struct hif_scatter_req*) ; 
 struct hif_scatter_req* hif_scatter_req_get (TYPE_2__*) ; 
 int /*<<< orphan*/  htc_async_tx_scat_complete ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ath6kl_htc_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath6kl_htc_tx_bundle(struct htc_endpoint *endpoint,
				 struct list_head *queue,
				 int *sent_bundle, int *n_bundle_pkts)
{
	struct htc_target *target = endpoint->target;
	struct hif_scatter_req *scat_req = NULL;
	int n_scat, n_sent_bundle = 0, tot_pkts_bundle = 0, i;
	struct htc_packet *packet;
	int status;
	u32 txb_mask;
	u8 ac = WMM_NUM_AC;

	if ((HTC_CTRL_RSVD_SVC != endpoint->svc_id) &&
	    (WMI_CONTROL_SVC != endpoint->svc_id))
		ac = target->dev->ar->ep2ac_map[endpoint->eid];

	while (true) {
		status = 0;
		n_scat = get_queue_depth(queue);
		n_scat = min(n_scat, target->msg_per_bndl_max);

		if (n_scat < HTC_MIN_HTC_MSGS_TO_BUNDLE)
			/* not enough to bundle */
			break;

		scat_req = hif_scatter_req_get(target->dev->ar);

		if (!scat_req) {
			/* no scatter resources  */
			ath6kl_dbg(ATH6KL_DBG_HTC,
				   "htc tx no more scatter resources\n");
			break;
		}

		if ((ac < WMM_NUM_AC) && (ac != WMM_AC_BK)) {
			if (WMM_AC_BE == ac)
				/*
				 * BE, BK have priorities and bit
				 * positions reversed
				 */
				txb_mask = (1 << WMM_AC_BK);
			else
				/*
				 * any AC with priority lower than
				 * itself
				 */
				txb_mask = ((1 << ac) - 1);

			/*
			 * when the scatter request resources drop below a
			 * certain threshold, disable Tx bundling for all
			 * AC's with priority lower than the current requesting
			 * AC. Otherwise re-enable Tx bundling for them
			 */
			if (scat_req->scat_q_depth < ATH6KL_SCATTER_REQS)
				target->tx_bndl_mask &= ~txb_mask;
			else
				target->tx_bndl_mask |= txb_mask;
		}

		ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx pkts to scatter: %d\n",
			   n_scat);

		scat_req->len = 0;
		scat_req->scat_entries = 0;

		status = ath6kl_htc_tx_setup_scat_list(target, endpoint,
						       scat_req, n_scat,
						       queue);
		if (status == -EAGAIN) {
			hif_scatter_req_add(target->dev->ar, scat_req);
			break;
		}

		/* send path is always asynchronous */
		scat_req->complete = htc_async_tx_scat_complete;
		n_sent_bundle++;
		tot_pkts_bundle += scat_req->scat_entries;

		ath6kl_dbg(ATH6KL_DBG_HTC,
			   "htc tx scatter bytes %d entries %d\n",
			   scat_req->len, scat_req->scat_entries);

		for (i = 0; i < scat_req->scat_entries; i++) {
			packet = scat_req->scat_list[i].packet;
			trace_ath6kl_htc_tx(packet->status, packet->endpoint,
					    packet->buf, packet->act_len);
		}

		ath6kl_hif_submit_scat_req(target->dev, scat_req, false);

		if (status)
			break;
	}

	*sent_bundle = n_sent_bundle;
	*n_bundle_pkts = tot_pkts_bundle;
	ath6kl_dbg(ATH6KL_DBG_HTC, "htc tx bundle sent %d pkts\n",
		   n_sent_bundle);

	return;
}