#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct efa_com_admin_queue {int dummy; } ;
struct efa_com_dev {int /*<<< orphan*/  efa_dev; struct efa_com_admin_queue aq; } ;
struct efa_admin_set_feature_resp {int dummy; } ;
struct TYPE_8__ {int feature_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  mem_addr_low; int /*<<< orphan*/  mem_addr_high; } ;
struct TYPE_7__ {scalar_t__ length; TYPE_2__ address; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  opcode; } ;
struct efa_admin_set_feature_cmd {TYPE_4__ feature_common; TYPE_3__ control_buffer; TYPE_1__ aq_common_descriptor; } ;
struct efa_admin_aq_entry {int dummy; } ;
struct efa_admin_acq_entry {int dummy; } ;
typedef  enum efa_admin_aq_feature_id { ____Placeholder_efa_admin_aq_feature_id } efa_admin_aq_feature_id ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK ; 
 int /*<<< orphan*/  EFA_ADMIN_SET_FEATURE ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  efa_com_check_supported_feature_id (struct efa_com_dev*,int) ; 
 int efa_com_cmd_exec (struct efa_com_admin_queue*,struct efa_admin_aq_entry*,int,struct efa_admin_acq_entry*,int) ; 
 int /*<<< orphan*/  efa_com_set_dma_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ibdev_err_ratelimited (int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static int efa_com_set_feature_ex(struct efa_com_dev *edev,
				  struct efa_admin_set_feature_resp *set_resp,
				  struct efa_admin_set_feature_cmd *set_cmd,
				  enum efa_admin_aq_feature_id feature_id,
				  dma_addr_t control_buf_dma_addr,
				  u32 control_buff_size)
{
	struct efa_com_admin_queue *aq;
	int err;

	if (!efa_com_check_supported_feature_id(edev, feature_id)) {
		ibdev_err_ratelimited(edev->efa_dev,
				      "Feature %d isn't supported\n",
				      feature_id);
		return -EOPNOTSUPP;
	}

	aq = &edev->aq;

	set_cmd->aq_common_descriptor.opcode = EFA_ADMIN_SET_FEATURE;
	if (control_buff_size) {
		set_cmd->aq_common_descriptor.flags =
			EFA_ADMIN_AQ_COMMON_DESC_CTRL_DATA_INDIRECT_MASK;
		efa_com_set_dma_addr(control_buf_dma_addr,
				     &set_cmd->control_buffer.address.mem_addr_high,
				     &set_cmd->control_buffer.address.mem_addr_low);
	}

	set_cmd->control_buffer.length = control_buff_size;
	set_cmd->feature_common.feature_id = feature_id;
	err = efa_com_cmd_exec(aq,
			       (struct efa_admin_aq_entry *)set_cmd,
			       sizeof(*set_cmd),
			       (struct efa_admin_acq_entry *)set_resp,
			       sizeof(*set_resp));

	if (err) {
		ibdev_err_ratelimited(
			edev->efa_dev,
			"Failed to submit set_feature command %d error: %d\n",
			feature_id, err);
		return err;
	}

	return 0;
}