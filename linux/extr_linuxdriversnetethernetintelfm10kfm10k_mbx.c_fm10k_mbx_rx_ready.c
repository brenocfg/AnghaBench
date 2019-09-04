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
struct fm10k_mbx_info {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 scalar_t__ fm10k_fifo_head_len (int /*<<< orphan*/ *) ; 
 scalar_t__ fm10k_fifo_used (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fm10k_mbx_rx_ready(struct fm10k_mbx_info *mbx)
{
	u16 msg_size = fm10k_fifo_head_len(&mbx->rx);

	return msg_size && (fm10k_fifo_used(&mbx->rx) >= msg_size);
}