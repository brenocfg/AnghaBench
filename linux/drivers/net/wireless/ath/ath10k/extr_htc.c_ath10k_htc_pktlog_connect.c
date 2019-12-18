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
struct TYPE_2__ {int /*<<< orphan*/ * ep_tx_credits; int /*<<< orphan*/  ep_rx_complete; int /*<<< orphan*/ * ep_tx_complete; } ;
struct ath10k_htc_svc_conn_resp {int /*<<< orphan*/  service_id; TYPE_1__ ep_ops; } ;
struct ath10k_htc_svc_conn_req {int /*<<< orphan*/  service_id; TYPE_1__ ep_ops; } ;
struct ath10k {int /*<<< orphan*/  htc; } ;
typedef  int /*<<< orphan*/  conn_resp ;
typedef  int /*<<< orphan*/  conn_req ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_HTC_SVC_ID_HTT_LOG_MSG ; 
 int ath10k_htc_connect_service (int /*<<< orphan*/ *,struct ath10k_htc_svc_conn_resp*,struct ath10k_htc_svc_conn_resp*) ; 
 int /*<<< orphan*/  ath10k_htc_pktlog_process_rx ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int /*<<< orphan*/  memset (struct ath10k_htc_svc_conn_resp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ath10k_htc_pktlog_connect(struct ath10k *ar)
{
	struct ath10k_htc_svc_conn_resp conn_resp;
	struct ath10k_htc_svc_conn_req conn_req;
	int status;

	memset(&conn_req, 0, sizeof(conn_req));
	memset(&conn_resp, 0, sizeof(conn_resp));

	conn_req.ep_ops.ep_tx_complete = NULL;
	conn_req.ep_ops.ep_rx_complete = ath10k_htc_pktlog_process_rx;
	conn_req.ep_ops.ep_tx_credits = NULL;

	/* connect to control service */
	conn_req.service_id = ATH10K_HTC_SVC_ID_HTT_LOG_MSG;
	status = ath10k_htc_connect_service(&ar->htc, &conn_req, &conn_resp);
	if (status) {
		ath10k_warn(ar, "failed to connect to PKTLOG service: %d\n",
			    status);
		return status;
	}

	return 0;
}