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
typedef  scalar_t__ u8 ;
struct fc_seq {int dummy; } ;
struct fc_lport {scalar_t__ state; int /*<<< orphan*/  lp_mutex; } ;
struct fc_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ ELS_LS_ACC ; 
 struct fc_frame* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_LPORT_DBG (struct fc_lport*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct fc_frame*) ; 
 scalar_t__ LPORT_ST_LOGO ; 
 int /*<<< orphan*/  fc_els_resp_type (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_frame_free (struct fc_frame*) ; 
 scalar_t__ fc_frame_payload_op (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_enter_disabled (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_error (struct fc_lport*,struct fc_frame*) ; 
 int /*<<< orphan*/  fc_lport_state (struct fc_lport*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fc_lport_logo_resp(struct fc_seq *sp, struct fc_frame *fp,
			void *lp_arg)
{
	struct fc_lport *lport = lp_arg;
	u8 op;

	FC_LPORT_DBG(lport, "Received a LOGO %s\n", fc_els_resp_type(fp));

	if (fp == ERR_PTR(-FC_EX_CLOSED))
		return;

	mutex_lock(&lport->lp_mutex);

	if (lport->state != LPORT_ST_LOGO) {
		FC_LPORT_DBG(lport, "Received a LOGO response, but in state "
			     "%s\n", fc_lport_state(lport));
		if (IS_ERR(fp))
			goto err;
		goto out;
	}

	if (IS_ERR(fp)) {
		fc_lport_error(lport, fp);
		goto err;
	}

	op = fc_frame_payload_op(fp);
	if (op == ELS_LS_ACC)
		fc_lport_enter_disabled(lport);
	else
		fc_lport_error(lport, fp);

out:
	fc_frame_free(fp);
err:
	mutex_unlock(&lport->lp_mutex);
}