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
typedef  int /*<<< orphan*/  u32 ;
struct venus_inst {int /*<<< orphan*/  core; } ;
struct venus_hfi_device {int dummy; } ;
struct hfi_session_set_property_pkt {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int IFACEQ_VAR_LARGE_PKT_SIZE ; 
 int pkt_session_set_property (struct hfi_session_set_property_pkt*,struct venus_inst*,int /*<<< orphan*/ ,void*) ; 
 struct venus_hfi_device* to_hfi_priv (int /*<<< orphan*/ ) ; 
 int venus_iface_cmdq_write (struct venus_hfi_device*,struct hfi_session_set_property_pkt*) ; 

__attribute__((used)) static int venus_session_set_property(struct venus_inst *inst, u32 ptype,
				      void *pdata)
{
	struct venus_hfi_device *hdev = to_hfi_priv(inst->core);
	struct hfi_session_set_property_pkt *pkt;
	u8 packet[IFACEQ_VAR_LARGE_PKT_SIZE];
	int ret;

	pkt = (struct hfi_session_set_property_pkt *)packet;

	ret = pkt_session_set_property(pkt, inst, ptype, pdata);
	if (ret == -ENOTSUPP)
		return 0;
	if (ret)
		return ret;

	return venus_iface_cmdq_write(hdev, pkt);
}