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
typedef  int u8 ;
typedef  enum mlxsw_reg_spms_state { ____Placeholder_mlxsw_reg_spms_state } mlxsw_reg_spms_state ;

/* Variables and functions */
#define  BR_STATE_BLOCKING 132 
#define  BR_STATE_DISABLED 131 
#define  BR_STATE_FORWARDING 130 
#define  BR_STATE_LEARNING 129 
#define  BR_STATE_LISTENING 128 
 int /*<<< orphan*/  BUG () ; 
 int MLXSW_REG_SPMS_STATE_DISCARDING ; 
 int MLXSW_REG_SPMS_STATE_FORWARDING ; 
 int MLXSW_REG_SPMS_STATE_LEARNING ; 

enum mlxsw_reg_spms_state mlxsw_sp_stp_spms_state(u8 state)
{
	switch (state) {
	case BR_STATE_FORWARDING:
		return MLXSW_REG_SPMS_STATE_FORWARDING;
	case BR_STATE_LEARNING:
		return MLXSW_REG_SPMS_STATE_LEARNING;
	case BR_STATE_LISTENING: /* fall-through */
	case BR_STATE_DISABLED: /* fall-through */
	case BR_STATE_BLOCKING:
		return MLXSW_REG_SPMS_STATE_DISCARDING;
	default:
		BUG();
	}
}