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
struct fm10k_mbx_info {int /*<<< orphan*/  local; int /*<<< orphan*/  tx; int /*<<< orphan*/  pulled; int /*<<< orphan*/  tail; scalar_t__ tail_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_fifo_crc (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_fifo_head_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fm10k_mbx_index_len (struct fm10k_mbx_info*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_mbx_update_local_crc(struct fm10k_mbx_info *mbx, u16 head)
{
	u16 len = mbx->tail_len - fm10k_mbx_index_len(mbx, head, mbx->tail);

	/* determine the offset for the start of the region to be pulled */
	head = fm10k_fifo_head_offset(&mbx->tx, mbx->pulled);

	/* update local CRC to include all of the pulled data */
	mbx->local = fm10k_fifo_crc(&mbx->tx, head, len, mbx->local);
}