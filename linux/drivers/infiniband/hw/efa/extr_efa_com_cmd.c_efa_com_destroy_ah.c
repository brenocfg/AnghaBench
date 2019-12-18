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
struct efa_com_destroy_ah_params {int /*<<< orphan*/  pdn; int /*<<< orphan*/  ah; } ;
struct efa_admin_destroy_ah_resp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  opcode; } ;
struct efa_admin_destroy_ah_cmd {int /*<<< orphan*/  pd; int /*<<< orphan*/  ah; TYPE_1__ aq_common_desc; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  int /*<<< orphan*/  cmd_completion ;
typedef  int /*<<< orphan*/  ah_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_DESTROY_AH ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int efa_com_destroy_ah(struct efa_com_dev *edev,
		       struct efa_com_destroy_ah_params *params)
{
	struct efa_admin_destroy_ah_resp cmd_completion;
	struct efa_admin_destroy_ah_cmd ah_cmd = {};
	struct efa_com_admin_queue *aq = &edev->aq;
	int err;

	ah_cmd.aq_common_desc.opcode = EFA_ADMIN_DESTROY_AH;
	ah_cmd.ah = params->ah;
	ah_cmd.pd = params->pdn;

	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)&ah_cmd,
			       sizeof(ah_cmd),
			       (struct efa_admin_acq_entry *)&cmd_completion,
			       sizeof(cmd_completion));
	if (err) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Failed to destroy ah-%d pd-%d [%d]\n",
				      ah_cmd.ah, ah_cmd.pd, err);
		return err;
	}

	return 0;
}