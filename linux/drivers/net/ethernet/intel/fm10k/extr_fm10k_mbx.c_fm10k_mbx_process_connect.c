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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  size; } ;
struct fm10k_mbx_info {int state; int /*<<< orphan*/  tail; TYPE_1__ rx; int /*<<< orphan*/  max_size; int /*<<< orphan*/  mbx_hdr; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  enum fm10k_mbx_state { ____Placeholder_fm10k_mbx_state } fm10k_mbx_state ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_SIZE ; 
 int /*<<< orphan*/  FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
#define  FM10K_STATE_CONNECT 130 
#define  FM10K_STATE_DISCONNECT 129 
#define  FM10K_STATE_OPEN 128 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  fm10k_mbx_connect_reset (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_mbx_create_reply (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_update_max_size (struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 fm10k_mbx_process_connect(struct fm10k_hw *hw,
				     struct fm10k_mbx_info *mbx)
{
	const enum fm10k_mbx_state state = mbx->state;
	const u32 *hdr = &mbx->mbx_hdr;
	u16 size, head;

	/* we will need to pull all of the fields for verification */
	size = FM10K_MSG_HDR_FIELD_GET(*hdr, CONNECT_SIZE);
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);

	switch (state) {
	case FM10K_STATE_DISCONNECT:
	case FM10K_STATE_OPEN:
		/* reset any in-progress work */
		fm10k_mbx_connect_reset(mbx);
		break;
	case FM10K_STATE_CONNECT:
		/* we cannot exit connect until the size is good */
		if (size > mbx->rx.size) {
			mbx->max_size = mbx->rx.size - 1;
		} else {
			/* record the remote system requesting connection */
			mbx->state = FM10K_STATE_OPEN;

			fm10k_mbx_update_max_size(mbx, size);
		}
		break;
	default:
		break;
	}

	/* align our tail index to remote head index */
	mbx->tail = head;

	return fm10k_mbx_create_reply(hw, mbx, head);
}