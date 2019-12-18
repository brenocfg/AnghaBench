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
struct fc_lport {int state; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame_header {scalar_t__ fh_type; } ;
struct fc_frame {int dummy; } ;
struct fc_ct_hdr {scalar_t__ ct_fs_type; scalar_t__ ct_fs_subtype; int /*<<< orphan*/  ct_cmd; int /*<<< orphan*/  ct_explan; int /*<<< orphan*/  ct_reason; } ;

/* Variables and functions */
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 scalar_t__ FC_FDMI_SUBTYPE ; 
 scalar_t__ FC_FST_MGMT ; 
 int /*<<< orphan*/  FC_FS_ACC ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ FC_TYPE_CT ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
#define  LPORT_ST_DHBA 131 
#define  LPORT_ST_DPRT 130 
#define  LPORT_ST_RHBA 129 
#define  LPORT_ST_RPA 128 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 struct fc_frame_header* fc_frame_header_get (struct fc_frame*) ; 
 struct fc_ct_hdr* fc_frame_payload_get (struct fc_frame*,int) ; 
 int /*<<< orphan*/  fc_lport_enter_ms (struct fc_lport*,int const) ; 
 int /*<<< orphan*/  fc_lport_enter_scr (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_error (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fc_lport_ms_resp(struct fc_seq *sp, struct fc_frame *fp,
			     void *lp_arg)
{
	struct fc_lport *lport = lp_arg;
	struct fc_frame_header *fh;
	struct fc_ct_hdr *ct;

	FC_LPORT_DBG(lport, "Received a ms %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		return;

	mutex_lock(&lport->lp_mutex);

	if (lport->state < LPORT_ST_RHBA || lport->state > LPORT_ST_DPRT) {
		FC_LPORT_DBG(lport, "Received a management server response, "
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
	    ct->ct_fs_type == FC_FST_MGMT &&
	    ct->ct_fs_subtype == FC_FDMI_SUBTYPE) {
		FC_LPORT_DBG(lport, "Received a management server response, "
				    "reason=%d explain=%d\n",
				    ct->ct_reason,
				    ct->ct_explan);

		switch (lport->state) {
		case LPORT_ST_RHBA:
			if (ntohs(ct->ct_cmd) == FC_FS_ACC)
				fc_lport_enter_ms(lport, LPORT_ST_RPA);
			else /* Error Skip RPA */
				fc_lport_enter_scr(lport);
			break;
		case LPORT_ST_RPA:
			fc_lport_enter_scr(lport);
			break;
		case LPORT_ST_DPRT:
			fc_lport_enter_ms(lport, LPORT_ST_RHBA);
			break;
		case LPORT_ST_DHBA:
			fc_lport_enter_ms(lport, LPORT_ST_DPRT);
			break;
		default:
			/* should have already been caught by state checks */
			break;
		}
	} else {
		/* Invalid Frame? */
		fc_lport_error(lport, fp);
	}
out:
	fc_frame_free(fp);
err:
	mutex_unlock(&lport->lp_mutex);
}