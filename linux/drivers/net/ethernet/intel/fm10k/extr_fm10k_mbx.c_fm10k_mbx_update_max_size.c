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
struct fm10k_mbx_info {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx; scalar_t__ max_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fm10k_fifo_head_drop (int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_fifo_head_len (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm10k_mbx_update_max_size(struct fm10k_mbx_info *mbx, u16 size)
{
	u16 len;

	mbx->max_size = size;

	/* flush any oversized messages from the queue */
	for (len = fm10k_fifo_head_len(&mbx->tx);
	     len > size;
	     len = fm10k_fifo_head_len(&mbx->tx)) {
		fm10k_fifo_head_drop(&mbx->tx);
		mbx->tx_dropped++;
	}
}