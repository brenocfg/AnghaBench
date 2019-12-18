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
typedef  int u32 ;
struct TYPE_2__ {int operation; } ;
struct hv_vss_msg {TYPE_1__ vss_hdr; } ;
typedef  int /*<<< orphan*/  our_ver ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
#define  VSS_OP_REGISTER 129 
#define  VSS_OP_REGISTER1 128 
 int dm_reg_value ; 
 int /*<<< orphan*/  hvt ; 
 int /*<<< orphan*/  hvutil_transport_send (int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  vss_register_done ; 

__attribute__((used)) static int vss_handle_handshake(struct hv_vss_msg *vss_msg)
{
	u32 our_ver = VSS_OP_REGISTER1;

	switch (vss_msg->vss_hdr.operation) {
	case VSS_OP_REGISTER:
		/* Daemon doesn't expect us to reply */
		dm_reg_value = VSS_OP_REGISTER;
		break;
	case VSS_OP_REGISTER1:
		/* Daemon expects us to reply with our own version */
		if (hvutil_transport_send(hvt, &our_ver, sizeof(our_ver),
					  vss_register_done))
			return -EFAULT;
		dm_reg_value = VSS_OP_REGISTER1;
		break;
	default:
		return -EINVAL;
	}
	pr_info("VSS: userspace daemon ver. %d connected\n", dm_reg_value);
	return 0;
}