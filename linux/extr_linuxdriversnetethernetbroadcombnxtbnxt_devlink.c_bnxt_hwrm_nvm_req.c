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
union devlink_param_value {int /*<<< orphan*/  vbool; } ;
typedef  scalar_t__ u32 ;
struct hwrm_nvm_get_variable_input {void* req_type; void* dimensions; void* index_0; void* option_num; void* data_len; int /*<<< orphan*/  dest_data_addr; } ;
struct bnxt_dl_nvm_param {scalar_t__ id; scalar_t__ dir_type; int num_bits; int offset; } ;
struct TYPE_3__ {int port_id; int fw_fid; } ;
struct bnxt {TYPE_2__* pdev; TYPE_1__ pf; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct bnxt_dl_nvm_param*) ; 
 int BITS_PER_BYTE ; 
 int BNXT_FIRST_PF_FID ; 
 scalar_t__ BNXT_NVM_FUNC_CFG ; 
 scalar_t__ BNXT_NVM_PORT_CFG ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int HWRM_NVM_GET_VARIABLE ; 
 int HWRM_NVM_SET_VARIABLE ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 void* dma_zalloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 struct bnxt_dl_nvm_param* nvm_params ; 
 int roundup (int,int) ; 

__attribute__((used)) static int bnxt_hwrm_nvm_req(struct bnxt *bp, u32 param_id, void *msg,
			     int msg_len, union devlink_param_value *val)
{
	struct hwrm_nvm_get_variable_input *req = msg;
	void *data_addr = NULL, *buf = NULL;
	struct bnxt_dl_nvm_param nvm_param;
	int bytesize, idx = 0, rc, i;
	dma_addr_t data_dma_addr;

	/* Get/Set NVM CFG parameter is supported only on PFs */
	if (BNXT_VF(bp))
		return -EPERM;

	for (i = 0; i < ARRAY_SIZE(nvm_params); i++) {
		if (nvm_params[i].id == param_id) {
			nvm_param = nvm_params[i];
			break;
		}
	}

	if (i == ARRAY_SIZE(nvm_params))
		return -EOPNOTSUPP;

	if (nvm_param.dir_type == BNXT_NVM_PORT_CFG)
		idx = bp->pf.port_id;
	else if (nvm_param.dir_type == BNXT_NVM_FUNC_CFG)
		idx = bp->pf.fw_fid - BNXT_FIRST_PF_FID;

	bytesize = roundup(nvm_param.num_bits, BITS_PER_BYTE) / BITS_PER_BYTE;
	if (nvm_param.num_bits == 1)
		buf = &val->vbool;

	data_addr = dma_zalloc_coherent(&bp->pdev->dev, bytesize,
					&data_dma_addr, GFP_KERNEL);
	if (!data_addr)
		return -ENOMEM;

	req->dest_data_addr = cpu_to_le64(data_dma_addr);
	req->data_len = cpu_to_le16(nvm_param.num_bits);
	req->option_num = cpu_to_le16(nvm_param.offset);
	req->index_0 = cpu_to_le16(idx);
	if (idx)
		req->dimensions = cpu_to_le16(1);

	if (req->req_type == cpu_to_le16(HWRM_NVM_SET_VARIABLE))
		memcpy(data_addr, buf, bytesize);

	rc = hwrm_send_message(bp, msg, msg_len, HWRM_CMD_TIMEOUT);
	if (!rc && req->req_type == cpu_to_le16(HWRM_NVM_GET_VARIABLE))
		memcpy(buf, data_addr, bytesize);

	dma_free_coherent(&bp->pdev->dev, bytesize, data_addr, data_dma_addr);
	if (rc)
		return -EIO;
	return 0;
}