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
struct TYPE_2__ {int /*<<< orphan*/ * cmd; } ;
struct ocrdma_mqe {TYPE_1__ u; } ;
struct ocrdma_mbx_hdr {int dummy; } ;
struct ocrdma_fw_conf_rsp {int dummy; } ;
struct ocrdma_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OCRDMA_CMD_GET_FW_CONFIG ; 
 int /*<<< orphan*/  OCRDMA_SUBSYS_COMMON ; 
 int /*<<< orphan*/  kfree (struct ocrdma_mqe*) ; 
 int ocrdma_check_fw_config (struct ocrdma_dev*,struct ocrdma_fw_conf_rsp*) ; 
 struct ocrdma_mqe* ocrdma_init_emb_mqe (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocrdma_init_mch (struct ocrdma_mbx_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ocrdma_mbx_cmd (struct ocrdma_dev*,struct ocrdma_mqe*) ; 

__attribute__((used)) static int ocrdma_mbx_query_fw_config(struct ocrdma_dev *dev)
{
	int status = -ENOMEM;
	struct ocrdma_mqe *cmd;
	struct ocrdma_fw_conf_rsp *rsp;

	cmd = ocrdma_init_emb_mqe(OCRDMA_CMD_GET_FW_CONFIG, sizeof(*cmd));
	if (!cmd)
		return -ENOMEM;
	ocrdma_init_mch((struct ocrdma_mbx_hdr *)&cmd->u.cmd[0],
			OCRDMA_CMD_GET_FW_CONFIG,
			OCRDMA_SUBSYS_COMMON, sizeof(*cmd));
	status = ocrdma_mbx_cmd(dev, (struct ocrdma_mqe *)cmd);
	if (status)
		goto mbx_err;
	rsp = (struct ocrdma_fw_conf_rsp *)cmd;
	status = ocrdma_check_fw_config(dev, rsp);
mbx_err:
	kfree(cmd);
	return status;
}