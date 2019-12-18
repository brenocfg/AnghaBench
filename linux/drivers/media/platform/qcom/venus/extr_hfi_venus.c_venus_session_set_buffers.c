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
typedef  int /*<<< orphan*/  u8 ;
struct venus_inst {int /*<<< orphan*/  core; } ;
struct venus_hfi_device {int dummy; } ;
struct hfi_session_set_buffers_pkt {int dummy; } ;
struct hfi_buffer_desc {scalar_t__ buffer_type; } ;

/* Variables and functions */
 scalar_t__ HFI_BUFFER_INPUT ; 
 int IFACEQ_VAR_LARGE_PKT_SIZE ; 
 int pkt_session_set_buffers (struct hfi_session_set_buffers_pkt*,struct venus_inst*,struct hfi_buffer_desc*) ; 
 struct venus_hfi_device* to_hfi_priv (int /*<<< orphan*/ ) ; 
 int venus_iface_cmdq_write (struct venus_hfi_device*,struct hfi_session_set_buffers_pkt*) ; 

__attribute__((used)) static int venus_session_set_buffers(struct venus_inst *inst,
				     struct hfi_buffer_desc *bd)
{
	struct venus_hfi_device *hdev = to_hfi_priv(inst->core);
	struct hfi_session_set_buffers_pkt *pkt;
	u8 packet[IFACEQ_VAR_LARGE_PKT_SIZE];
	int ret;

	if (bd->buffer_type == HFI_BUFFER_INPUT)
		return 0;

	pkt = (struct hfi_session_set_buffers_pkt *)packet;

	ret = pkt_session_set_buffers(pkt, inst, bd);
	if (ret)
		return ret;

	return venus_iface_cmdq_write(hdev, pkt);
}