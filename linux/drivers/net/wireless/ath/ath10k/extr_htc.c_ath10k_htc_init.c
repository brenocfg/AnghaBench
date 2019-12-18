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
struct TYPE_2__ {int /*<<< orphan*/  ep_rx_complete; int /*<<< orphan*/  ep_tx_complete; } ;
struct ath10k_htc_svc_conn_resp {int /*<<< orphan*/  service_id; int /*<<< orphan*/  max_send_queue_depth; TYPE_1__ ep_ops; } ;
struct ath10k_htc_svc_conn_req {int /*<<< orphan*/  service_id; int /*<<< orphan*/  max_send_queue_depth; TYPE_1__ ep_ops; } ;
struct ath10k_htc {int /*<<< orphan*/  ctl_resp; struct ath10k* ar; int /*<<< orphan*/  tx_lock; } ;
struct ath10k {struct ath10k_htc htc; } ;
typedef  int /*<<< orphan*/  conn_resp ;
typedef  int /*<<< orphan*/  conn_req ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_SVC_ID_RSVD_CTRL ; 
 int /*<<< orphan*/  ATH10K_NUM_CONTROL_TX_BUFFERS ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,int) ; 
 int ath10k_htc_connect_service (struct ath10k_htc*,struct ath10k_htc_svc_conn_resp*,struct ath10k_htc_svc_conn_resp*) ; 
 int /*<<< orphan*/  ath10k_htc_control_rx_complete ; 
 int /*<<< orphan*/  ath10k_htc_control_tx_complete ; 
 int /*<<< orphan*/  ath10k_htc_reset_endpoint_states (struct ath10k_htc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ath10k_htc_svc_conn_resp*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int ath10k_htc_init(struct ath10k *ar)
{
	int status;
	struct ath10k_htc *htc = &ar->htc;
	struct ath10k_htc_svc_conn_req conn_req;
	struct ath10k_htc_svc_conn_resp conn_resp;

	spin_lock_init(&htc->tx_lock);

	ath10k_htc_reset_endpoint_states(htc);

	htc->ar = ar;

	/* setup our pseudo HTC control endpoint connection */
	memset(&conn_req, 0, sizeof(conn_req));
	memset(&conn_resp, 0, sizeof(conn_resp));
	conn_req.ep_ops.ep_tx_complete = ath10k_htc_control_tx_complete;
	conn_req.ep_ops.ep_rx_complete = ath10k_htc_control_rx_complete;
	conn_req.max_send_queue_depth = ATH10K_NUM_CONTROL_TX_BUFFERS;
	conn_req.service_id = ATH10K_HTC_SVC_ID_RSVD_CTRL;

	/* connect fake service */
	status = ath10k_htc_connect_service(htc, &conn_req, &conn_resp);
	if (status) {
		ath10k_err(ar, "could not connect to htc service (%d)\n",
			   status);
		return status;
	}

	init_completion(&htc->ctl_resp);

	return 0;
}