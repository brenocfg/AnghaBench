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
typedef  scalar_t__ u8 ;
struct fc_seq {int dummy; } ;
struct TYPE_2__ {scalar_t__ port_id; scalar_t__ port_name; scalar_t__ node_name; } ;
struct fc_rport_priv {scalar_t__ rp_state; int /*<<< orphan*/  kref; int /*<<< orphan*/  rp_mutex; TYPE_1__ ids; } ;
struct fc_frame {int dummy; } ;
struct fc_els_adisc {int /*<<< orphan*/  adisc_wwnn; int /*<<< orphan*/  adisc_wwpn; int /*<<< orphan*/  adisc_port_id; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*,...) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  PTR_ERR (struct fc_frame*) ; 
 scalar_t__ RPORT_ST_ADISC ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_adisc* fc_frame_payload_get (struct fc_frame*,int) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_rport_destroy ; 
 int /*<<< orphan*/  fc_rport_enter_flogi (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_enter_ready (struct fc_rport_priv*) ; 
 int /*<<< orphan*/  fc_rport_error (struct fc_rport_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_rport_state (struct fc_rport_priv*) ; 
 scalar_t__ get_unaligned_be64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ntoh24 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_rport_adisc_resp(struct fc_seq *sp, struct fc_frame *fp,
				void *rdata_arg)
{
	struct fc_rport_priv *rdata = rdata_arg;
	struct fc_els_adisc *adisc;
	u8 op;

	FC_RPORT_DBG(rdata, "Received a ADISC response\n");

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		goto put;

	mutex_lock(&rdata->rp_mutex);

	if (rdata->rp_state != RPORT_ST_ADISC) {
		FC_RPORT_DBG(rdata, "Received a ADISC resp but in state %s\n",
			     fc_rport_state(rdata));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_rport_error(rdata, PTR_ERR(fp));
		goto err;
	}

	/*
	 * If address verification failed.  Consider us logged out of the rport.
	 * Since the rport is still in discovery, we want to be
	 * logged in, so go to PLOGI state.  Otherwise, go back to READY.
	 */
	op = fc_frame_payload_op(fp);
	adisc = fc_frame_payload_get(fp, sizeof(*adisc));
	if (op != ELS_LS_ACC || !adisc ||
	    ntoh24(adisc->adisc_port_id) != rdata->ids.port_id ||
	    get_unaligned_be64(&adisc->adisc_wwpn) != rdata->ids.port_name ||
	    get_unaligned_be64(&adisc->adisc_wwnn) != rdata->ids.node_name) {
		FC_RPORT_DBG(rdata, "ADISC error or mismatch\n");
		fc_rport_enter_flogi(rdata);
	} else {
		FC_RPORT_DBG(rdata, "ADISC OK\n");
		fc_rport_enter_ready(rdata);
	}
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&rdata->rp_mutex);
put:
	kref_put(&rdata->kref, fc_rport_destroy);
}