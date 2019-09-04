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
struct venus_inst {int /*<<< orphan*/  core; } ;
struct venus_hfi_device {int dummy; } ;
struct hfi_session_pkt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pkt_session_cmd (struct hfi_session_pkt*,int /*<<< orphan*/ ,struct venus_inst*) ; 
 struct venus_hfi_device* to_hfi_priv (int /*<<< orphan*/ ) ; 
 int venus_iface_cmdq_write (struct venus_hfi_device*,struct hfi_session_pkt*) ; 

__attribute__((used)) static int venus_session_cmd(struct venus_inst *inst, u32 pkt_type)
{
	struct venus_hfi_device *hdev = to_hfi_priv(inst->core);
	struct hfi_session_pkt pkt;

	pkt_session_cmd(&pkt, pkt_type, inst);

	return venus_iface_cmdq_write(hdev, &pkt);
}