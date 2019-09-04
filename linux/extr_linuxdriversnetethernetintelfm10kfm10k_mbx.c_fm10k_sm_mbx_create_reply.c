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
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_mbx_info {int state; int /*<<< orphan*/  remote; int /*<<< orphan*/  tail_len; } ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
#define  FM10K_STATE_CLOSED 131 
#define  FM10K_STATE_CONNECT 130 
#define  FM10K_STATE_DISCONNECT 129 
#define  FM10K_STATE_OPEN 128 
 int /*<<< orphan*/  fm10k_sm_mbx_create_connect_hdr (struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_create_data_hdr (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_sm_mbx_transmit (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_sm_mbx_create_reply(struct fm10k_hw *hw,
				      struct fm10k_mbx_info *mbx, u16 head)
{
	switch (mbx->state) {
	case FM10K_STATE_OPEN:
	case FM10K_STATE_DISCONNECT:
		/* flush out Tx data */
		fm10k_sm_mbx_transmit(hw, mbx, head);

		/* generate new header based on data */
		if (mbx->tail_len || (mbx->state == FM10K_STATE_OPEN)) {
			fm10k_sm_mbx_create_data_hdr(mbx);
		} else {
			mbx->remote = 0;
			fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		}
		break;
	case FM10K_STATE_CONNECT:
	case FM10K_STATE_CLOSED:
		fm10k_sm_mbx_create_connect_hdr(mbx, 0);
		break;
	default:
		break;
	}
}