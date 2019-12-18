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
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_com_dereg_mr_params {int /*<<< orphan*/  l_key; } ;
struct efa_admin_dereg_mr_resp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_dereg_mr_cmd {int /*<<< orphan*/  l_key; TYPE_1__ aq_common_desc; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  mr_cmd ;
typedef  int /*<<< orphan*/  cmd_completion ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_DEREG_MR ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

int efa_com_dereg_mr(struct efa_com_dev *edev,
		     struct efa_com_dereg_mr_params *params)
{
	struct efa_admin_dereg_mr_resp cmd_completion;
	struct efa_com_admin_queue *aq = &edev->aq;
	struct efa_admin_dereg_mr_cmd mr_cmd = {};
	int err;

	mr_cmd.aq_common_desc.opcode = EFA_ADMIN_DEREG_MR;
	mr_cmd.l_key = params->l_key;

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&mr_cmd,
			       sizeof(mr_cmd),
			       (struct efa_admin_acq_entry *)&cmd_completion,
			       sizeof(cmd_completion));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to de-register mr(lkey-%u) [%d]\n",
				      mr_cmd.l_key, err);
		return err;
	}

	return 0;
}