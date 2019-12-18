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
struct fc_seq {int dummy; } ;
struct fc_lport {int state; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  fdmi_enabled; } ;
struct fc_frame_header {scalar_t__ fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc_ct_hdr {scalar_t__ ct_fs_type; scalar_t__ ct_fs_subtype; int /*<<< orphan*/  ct_cmd; } ;

/* Variables and functions */
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 scalar_t__ FC_FST_DIR ; 
 scalar_t__ FC_FS_ACC ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FC_NS_SUBTYPE ; 
 scalar_t__ FC_TYPE_CT ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
#define  LPORT_ST_RFF_ID 132 
#define  LPORT_ST_RFT_ID 131 
#define  LPORT_ST_RNN_ID 130 
#define  LPORT_ST_RSNN_NN 129 
#define  LPORT_ST_RSPN_ID 128 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ct_hdr* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_lport_enter_fdmi (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_enter_ns (struct fc_lport*,int) ; 
 int /*<<< orphan*/  fc_lport_enter_scr (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_error (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_lport_ns_resp(struct fc_seq *sp, struct fc_frame *fp,
			     void *lp_arg)
{
	struct fc_lport *lport = lp_arg;
	struct fc_frame_header *fh;
	struct fc_ct_hdr *ct;

	FC_LPORT_DBG(lport, "Received a ns %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		return;

	mutex_lock(&lport->lp_mutex);

	if (lport->state < LPORT_ST_RNN_ID || lport->state > LPORT_ST_RFF_ID) {
		FC_LPORT_DBG(lport, "Received a name server response, "
			     "but in state %s\n", fc_lport_state(lport));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_lport_error(lport, fp);
		goto err;
	}

	fh = fc_frame_header_get(fp);
	ct = fc_frame_payload_get(fp, sizeof(*ct));

	if (fh && ct && fh->fh_type == FC_TYPE_CT &&
	    ct->ct_fs_type == FC_FST_DIR &&
	    ct->ct_fs_subtype == FC_NS_SUBTYPE &&
	    ntohs(ct->ct_cmd) == FC_FS_ACC)
		switch (lport->state) {
		case LPORT_ST_RNN_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RSNN_NN);
			break;
		case LPORT_ST_RSNN_NN:
			fc_lport_enter_ns(lport, LPORT_ST_RSPN_ID);
			break;
		case LPORT_ST_RSPN_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RFT_ID);
			break;
		case LPORT_ST_RFT_ID:
			fc_lport_enter_ns(lport, LPORT_ST_RFF_ID);
			break;
		case LPORT_ST_RFF_ID:
			if (lport->fdmi_enabled)
				fc_lport_enter_fdmi(lport);
			else
				fc_lport_enter_scr(lport);
			break;
		default:
			/* should have already been caught by state checks */
			break;
		}
	else
		fc_lport_error(lport, fp);
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&lport->lp_mutex);
}