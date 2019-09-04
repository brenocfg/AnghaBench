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
typedef  scalar_t__ u16 ;
struct fm10k_mbx_fifo {int /*<<< orphan*/  tail; } ;
struct fm10k_mbx_info {scalar_t__ pushed; int /*<<< orphan*/  rx_dwords; int /*<<< orphan*/  rx_messages; scalar_t__ head_len; int /*<<< orphan*/  head; struct fm10k_mbx_fifo rx; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_ERR_SIZE ; 
 scalar_t__ fm10k_fifo_unused (struct fm10k_mbx_fifo*) ; 
 int /*<<< orphan*/  fm10k_mbx_head_add (struct fm10k_mbx_info*,scalar_t__) ; 
 scalar_t__ fm10k_mbx_index_len (struct fm10k_mbx_info*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fm10k_mbx_pushed_tail_len (struct fm10k_mbx_info*) ; 
 int /*<<< orphan*/  fm10k_mbx_read_copy (struct fm10k_hw*,struct fm10k_mbx_info*) ; 
 scalar_t__ fm10k_mbx_validate_msg_size (struct fm10k_mbx_info*,scalar_t__) ; 

__attribute__((used)) static s32 fm10k_mbx_push_tail(struct fm10k_hw *hw,
			       struct fm10k_mbx_info *mbx,
			       u16 tail)
{
	struct fm10k_mbx_fifo *fifo = &mbx->rx;
	u16 len, seq = fm10k_mbx_index_len(mbx, mbx->head, tail);

	/* determine length of data to push */
	len = fm10k_fifo_unused(fifo) - mbx->pushed;
	if (len > seq)
		len = seq;

	/* update head and record bytes received */
	mbx->head = fm10k_mbx_head_add(mbx, len);
	mbx->head_len = len;

	/* nothing to do if there is no data */
	if (!len)
		return 0;

	/* Copy msg into Rx FIFO */
	fm10k_mbx_read_copy(hw, mbx);

	/* determine if there are any invalid lengths in message */
	if (fm10k_mbx_validate_msg_size(mbx, len))
		return FM10K_MBX_ERR_SIZE;

	/* Update pushed */
	mbx->pushed += len;

	/* flush any completed messages */
	for (len = fm10k_mbx_pushed_tail_len(mbx);
	     len && (mbx->pushed >= len);
	     len = fm10k_mbx_pushed_tail_len(mbx)) {
		fifo->tail += len;
		mbx->pushed -= len;
		mbx->rx_messages++;
		mbx->rx_dwords += len;
	}

	return 0;
}