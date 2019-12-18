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
typedef  int u16 ;
struct rsi_hw {int /*<<< orphan*/  ps_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_ZONE ; 
 int PS_CONFIRM_INDEX ; 
 int /*<<< orphan*/  PS_DISABLE_REQ_SENT ; 
 int /*<<< orphan*/  PS_ENABLED ; 
 int /*<<< orphan*/  PS_ENABLE_REQ_SENT ; 
 int /*<<< orphan*/  PS_NONE ; 
#define  RSI_SLEEP_REQUEST 129 
#define  RSI_WAKEUP_REQUEST 128 
 int get_unaligned_le16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsi_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rsi_modify_ps_state (struct rsi_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_psstate (int /*<<< orphan*/ ) ; 

int rsi_handle_ps_confirm(struct rsi_hw *adapter, u8 *msg)
{
	u16 cfm_type = get_unaligned_le16(msg + PS_CONFIRM_INDEX);

	switch (cfm_type) {
	case RSI_SLEEP_REQUEST:
		if (adapter->ps_state == PS_ENABLE_REQ_SENT)
			rsi_modify_ps_state(adapter, PS_ENABLED);
		break;
	case RSI_WAKEUP_REQUEST:
		if (adapter->ps_state == PS_DISABLE_REQ_SENT)
			rsi_modify_ps_state(adapter, PS_NONE);
		break;
	default:
		rsi_dbg(ERR_ZONE,
			"Invalid PS confirm type %x in state %s\n",
			cfm_type, str_psstate(adapter->ps_state));
		return -1;
	}

	return 0;
}