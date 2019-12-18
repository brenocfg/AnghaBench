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
struct fc_seq_els_data {int /*<<< orphan*/  explan; int /*<<< orphan*/  reason; } ;
struct fc_rport_priv {int /*<<< orphan*/  rp_mutex; struct fc_lport* local_port; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* frame_send ) (struct fc_lport*,struct fc_frame*) ;} ;
struct fc_lport {TYPE_1__ tt; int /*<<< orphan*/  e_d_tov; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;
struct fc_els_rtv_acc {scalar_t__ rtv_toq; void* rtv_e_d_tov; void* rtv_r_a_tov; int /*<<< orphan*/  rtv_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELS_EXPL_INSUF_RES ; 
 int /*<<< orphan*/  ELS_LS_ACC ; 
 int /*<<< orphan*/  ELS_LS_RJT ; 
 int /*<<< orphan*/  ELS_RJT_UNAB ; 
 int /*<<< orphan*/  FC_RCTL_ELS_REP ; 
 int /*<<< orphan*/  FC_RPORT_DBG (struct fc_rport_priv*,char*) ; 
 int /*<<< orphan*/  fc_fill_reply_hdr (struct fc_frame*,struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_els_rtv_acc* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_seq_els_rsp_send (struct fc_frame*,int /*<<< orphan*/ ,struct fc_seq_els_data*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fc_lport*,struct fc_frame*) ; 

__attribute__((used)) static void fc_rport_recv_rtv_req(struct fc_rport_priv *rdata,
				  struct fc_frame *in_fp)
{
	struct fc_lport *lport = rdata->local_port;
	struct fc_frame *fp;
	struct fc_els_rtv_acc *rtv;
	struct fc_seq_els_data rjt_data;

	lockdep_assert_held(&rdata->rp_mutex);
	lockdep_assert_held(&lport->lp_mutex);

	FC_RPORT_DBG(rdata, "Received RTV request\n");

	fp = fc_frame_alloc(lport, sizeof(*rtv));
	if (!fp) {
		rjt_data.reason = ELS_RJT_UNAB;
		rjt_data.explan = ELS_EXPL_INSUF_RES;
		fc_seq_els_rsp_send(in_fp, ELS_LS_RJT, &rjt_data);
		goto drop;
	}
	rtv = fc_frame_payload_get(fp, sizeof(*rtv));
	rtv->rtv_cmd = ELS_LS_ACC;
	rtv->rtv_r_a_tov = htonl(lport->r_a_tov);
	rtv->rtv_e_d_tov = htonl(lport->e_d_tov);
	rtv->rtv_toq = 0;
	fc_fill_reply_hdr(fp, in_fp, FC_RCTL_ELS_REP, 0);
	lport->tt.frame_send(lport, fp);
drop:
	fc_frame_free(in_fp);
}