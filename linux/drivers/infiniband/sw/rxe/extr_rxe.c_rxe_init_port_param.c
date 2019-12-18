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
struct TYPE_2__ {int /*<<< orphan*/  phys_state; int /*<<< orphan*/  active_speed; int /*<<< orphan*/  active_width; int /*<<< orphan*/  init_type_reply; int /*<<< orphan*/  subnet_timeout; int /*<<< orphan*/  sm_sl; int /*<<< orphan*/  max_vl_num; int /*<<< orphan*/  lmc; int /*<<< orphan*/  sm_lid; int /*<<< orphan*/  lid; int /*<<< orphan*/  pkey_tbl_len; int /*<<< orphan*/  qkey_viol_cntr; int /*<<< orphan*/  bad_pkey_cntr; int /*<<< orphan*/  max_msg_sz; int /*<<< orphan*/  port_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  active_mtu; int /*<<< orphan*/  max_mtu; int /*<<< orphan*/  state; } ;
struct rxe_port {int /*<<< orphan*/  subnet_prefix; int /*<<< orphan*/  mtu_cap; TYPE_1__ attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MTU_256 ; 
 int /*<<< orphan*/  IB_MTU_4096 ; 
 int /*<<< orphan*/  IB_PORT_DOWN ; 
 int /*<<< orphan*/  RXE_PORT_ACTIVE_SPEED ; 
 int /*<<< orphan*/  RXE_PORT_ACTIVE_WIDTH ; 
 int /*<<< orphan*/  RXE_PORT_BAD_PKEY_CNTR ; 
 int /*<<< orphan*/  RXE_PORT_GID_TBL_LEN ; 
 int /*<<< orphan*/  RXE_PORT_INIT_TYPE_REPLY ; 
 int /*<<< orphan*/  RXE_PORT_LID ; 
 int /*<<< orphan*/  RXE_PORT_LMC ; 
 int /*<<< orphan*/  RXE_PORT_MAX_MSG_SZ ; 
 int /*<<< orphan*/  RXE_PORT_MAX_VL_NUM ; 
 int /*<<< orphan*/  RXE_PORT_PHYS_STATE ; 
 int /*<<< orphan*/  RXE_PORT_PKEY_TBL_LEN ; 
 int /*<<< orphan*/  RXE_PORT_PORT_CAP_FLAGS ; 
 int /*<<< orphan*/  RXE_PORT_QKEY_VIOL_CNTR ; 
 int /*<<< orphan*/  RXE_PORT_SM_LID ; 
 int /*<<< orphan*/  RXE_PORT_SM_SL ; 
 int /*<<< orphan*/  RXE_PORT_SUBNET_PREFIX ; 
 int /*<<< orphan*/  RXE_PORT_SUBNET_TIMEOUT ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_mtu_enum_to_int (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rxe_init_port_param(struct rxe_port *port)
{
	port->attr.state		= IB_PORT_DOWN;
	port->attr.max_mtu		= IB_MTU_4096;
	port->attr.active_mtu		= IB_MTU_256;
	port->attr.gid_tbl_len		= RXE_PORT_GID_TBL_LEN;
	port->attr.port_cap_flags	= RXE_PORT_PORT_CAP_FLAGS;
	port->attr.max_msg_sz		= RXE_PORT_MAX_MSG_SZ;
	port->attr.bad_pkey_cntr	= RXE_PORT_BAD_PKEY_CNTR;
	port->attr.qkey_viol_cntr	= RXE_PORT_QKEY_VIOL_CNTR;
	port->attr.pkey_tbl_len		= RXE_PORT_PKEY_TBL_LEN;
	port->attr.lid			= RXE_PORT_LID;
	port->attr.sm_lid		= RXE_PORT_SM_LID;
	port->attr.lmc			= RXE_PORT_LMC;
	port->attr.max_vl_num		= RXE_PORT_MAX_VL_NUM;
	port->attr.sm_sl		= RXE_PORT_SM_SL;
	port->attr.subnet_timeout	= RXE_PORT_SUBNET_TIMEOUT;
	port->attr.init_type_reply	= RXE_PORT_INIT_TYPE_REPLY;
	port->attr.active_width		= RXE_PORT_ACTIVE_WIDTH;
	port->attr.active_speed		= RXE_PORT_ACTIVE_SPEED;
	port->attr.phys_state		= RXE_PORT_PHYS_STATE;
	port->mtu_cap			= ib_mtu_enum_to_int(IB_MTU_256);
	port->subnet_prefix		= cpu_to_be64(RXE_PORT_SUBNET_PREFIX);

	return 0;
}