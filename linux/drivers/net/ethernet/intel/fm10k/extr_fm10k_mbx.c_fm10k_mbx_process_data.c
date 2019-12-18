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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct fm10k_mbx_info {scalar_t__ state; int /*<<< orphan*/  tail; int /*<<< orphan*/  mbx_hdr; } ;
struct fm10k_hw {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MSG_HDR_FIELD_GET (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 scalar_t__ FM10K_STATE_CONNECT ; 
 scalar_t__ FM10K_STATE_OPEN ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  TAIL ; 
 scalar_t__ fm10k_mbx_create_reply (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm10k_mbx_dequeue_rx (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_push_tail (struct fm10k_hw*,struct fm10k_mbx_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_mbx_verify_remote_crc (struct fm10k_mbx_info*) ; 

__attribute__((used)) static s32 fm10k_mbx_process_data(struct fm10k_hw *hw,
				  struct fm10k_mbx_info *mbx)
{
	const u32 *hdr = &mbx->mbx_hdr;
	u16 head, tail;
	s32 err;

	/* we will need to pull all of the fields for verification */
	head = FM10K_MSG_HDR_FIELD_GET(*hdr, HEAD);
	tail = FM10K_MSG_HDR_FIELD_GET(*hdr, TAIL);

	/* if we are in connect just update our data and go */
	if (mbx->state == FM10K_STATE_CONNECT) {
		mbx->tail = head;
		mbx->state = FM10K_STATE_OPEN;
	}

	/* abort on message size errors */
	err = fm10k_mbx_push_tail(hw, mbx, tail);
	if (err < 0)
		return err;

	/* verify the checksum on the incoming data */
	err = fm10k_mbx_verify_remote_crc(mbx);
	if (err)
		return err;

	/* process messages if we have received any */
	fm10k_mbx_dequeue_rx(hw, mbx);

	return fm10k_mbx_create_reply(hw, mbx, head);
}