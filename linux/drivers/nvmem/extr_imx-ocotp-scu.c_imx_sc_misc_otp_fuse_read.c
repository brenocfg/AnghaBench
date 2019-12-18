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
typedef  int /*<<< orphan*/  u32 ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_misc_fuse_read {int /*<<< orphan*/  word; struct imx_sc_rpc_msg hdr; } ;
struct imx_sc_ipc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_MISC_FUNC_OTP_FUSE_READ ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_MISC ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int imx_scu_call_rpc (struct imx_sc_ipc*,struct imx_sc_msg_misc_fuse_read*,int) ; 

__attribute__((used)) static int imx_sc_misc_otp_fuse_read(struct imx_sc_ipc *ipc, u32 word,
				     u32 *val)
{
	struct imx_sc_msg_misc_fuse_read msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_MISC;
	hdr->func = IMX_SC_MISC_FUNC_OTP_FUSE_READ;
	hdr->size = 2;

	msg.word = word;

	ret = imx_scu_call_rpc(ipc, &msg, true);
	if (ret)
		return ret;

	*val = msg.word;

	return 0;
}