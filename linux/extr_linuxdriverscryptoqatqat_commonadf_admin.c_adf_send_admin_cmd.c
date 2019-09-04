#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ status; } ;
struct icp_qat_fw_init_admin_resp {int init_admin_cmd_id; int init_cfg_sz; TYPE_2__ init_resp_hdr; int /*<<< orphan*/  init_cfg_ptr; } ;
struct icp_qat_fw_init_admin_req {int init_admin_cmd_id; int init_cfg_sz; TYPE_2__ init_resp_hdr; int /*<<< orphan*/  init_cfg_ptr; } ;
struct adf_hw_device_data {int (* get_num_aes ) (struct adf_hw_device_data*) ;} ;
struct adf_accel_dev {TYPE_1__* admin; struct adf_hw_device_data* hw_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  const_tbl_addr; } ;

/* Variables and functions */
 int EFAULT ; 
 int ICP_QAT_FW_CONSTANTS_CFG ; 
 scalar_t__ adf_put_admin_msg_sync (struct adf_accel_dev*,int,struct icp_qat_fw_init_admin_resp*,struct icp_qat_fw_init_admin_resp*) ; 
 int /*<<< orphan*/  memset (struct icp_qat_fw_init_admin_resp*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct adf_hw_device_data*) ; 

__attribute__((used)) static int adf_send_admin_cmd(struct adf_accel_dev *accel_dev, int cmd)
{
	struct adf_hw_device_data *hw_device = accel_dev->hw_device;
	struct icp_qat_fw_init_admin_req req;
	struct icp_qat_fw_init_admin_resp resp;
	int i;

	memset(&req, 0, sizeof(struct icp_qat_fw_init_admin_req));
	req.init_admin_cmd_id = cmd;

	if (cmd == ICP_QAT_FW_CONSTANTS_CFG) {
		req.init_cfg_sz = 1024;
		req.init_cfg_ptr = accel_dev->admin->const_tbl_addr;
	}
	for (i = 0; i < hw_device->get_num_aes(hw_device); i++) {
		memset(&resp, 0, sizeof(struct icp_qat_fw_init_admin_resp));
		if (adf_put_admin_msg_sync(accel_dev, i, &req, &resp) ||
		    resp.init_resp_hdr.status)
			return -EFAULT;
	}
	return 0;
}