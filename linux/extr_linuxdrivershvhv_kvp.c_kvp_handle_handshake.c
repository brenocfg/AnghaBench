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
struct TYPE_2__ {int operation; } ;
struct hv_kvp_msg {TYPE_1__ kvp_hdr; } ;

/* Variables and functions */
 int EINVAL ; 
#define  KVP_OP_REGISTER 129 
#define  KVP_OP_REGISTER1 128 
 int dm_reg_value ; 
 int /*<<< orphan*/  kvp_register (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 

__attribute__((used)) static int kvp_handle_handshake(struct hv_kvp_msg *msg)
{
	switch (msg->kvp_hdr.operation) {
	case KVP_OP_REGISTER:
		dm_reg_value = KVP_OP_REGISTER;
		pr_info("KVP: IP injection functionality not available\n");
		pr_info("KVP: Upgrade the KVP daemon\n");
		break;
	case KVP_OP_REGISTER1:
		dm_reg_value = KVP_OP_REGISTER1;
		break;
	default:
		pr_info("KVP: incompatible daemon\n");
		pr_info("KVP: KVP version: %d, Daemon version: %d\n",
			KVP_OP_REGISTER1, msg->kvp_hdr.operation);
		return -EINVAL;
	}

	/*
	 * We have a compatible daemon; complete the handshake.
	 */
	pr_debug("KVP: userspace daemon ver. %d connected\n",
		 msg->kvp_hdr.operation);
	kvp_register(dm_reg_value);

	return 0;
}