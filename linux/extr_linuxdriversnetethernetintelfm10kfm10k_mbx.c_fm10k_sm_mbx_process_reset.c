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
struct fm10k_mbx_info {int state; int /*<<< orphan*/  tail; int /*<<< orphan*/  local; int /*<<< orphan*/  remote; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum fm10k_mbx_state { ____Placeholder_fm10k_mbx_state } fm10k_mbx_state ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_RESET_REQUESTED ; 
 int FM10K_STATE_CLOSED ; 
#define  FM10K_STATE_CONNECT 130 
#define  FM10K_STATE_DISCONNECT 129 
#define  FM10K_STATE_OPEN 128 
 int /*<<< orphan*/  fm10k_sm_mbx_connect_reset (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_create_reply (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_sm_mbx_process_reset(struct fm10k_hw *hw,
				      struct fm10k_mbx_info *mbx)
{
	s32 err = 0;
	const enum fm10k_mbx_state state = mbx->state;

	switch (state) {
	case FM10K_STATE_DISCONNECT:
		/* drop remote connections and disconnect */
		mbx->state = FM10K_STATE_CLOSED;
		mbx->remote = 0;
		mbx->local = 0;
		break;
	case FM10K_STATE_OPEN:
		/* flush any incomplete work */
		fm10k_sm_mbx_connect_reset(mbx);
		err = FM10K_ERR_RESET_REQUESTED;
		break;
	case FM10K_STATE_CONNECT:
		/* Update remote value to match local value */
		mbx->remote = mbx->local;
	default:
		break;
	}

	fm10k_sm_mbx_create_reply(hw, mbx, mbx->tail);

	return err;
}