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
struct pinctrl_dev {int dummy; } ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_resp_pad_get {unsigned long val; } ;
struct imx_sc_msg_req_pad_get {unsigned int pad; struct imx_sc_rpc_msg hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PAD_FUNC_GET ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PAD ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_req_pad_get*,int) ; 
 int /*<<< orphan*/  pinctrl_ipc_handle ; 

int imx_pinconf_get_scu(struct pinctrl_dev *pctldev, unsigned pin_id,
			unsigned long *config)
{
	struct imx_sc_msg_req_pad_get msg;
	struct imx_sc_msg_resp_pad_get *resp;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PAD;
	hdr->func = IMX_SC_PAD_FUNC_GET;
	hdr->size = 2;

	msg.pad = pin_id;

	ret = imx_scu_call_rpc(pinctrl_ipc_handle, &msg, true);
	if (ret)
		return ret;

	resp = (struct imx_sc_msg_resp_pad_get *)&msg;
	*config = resp->val;

	return 0;
}