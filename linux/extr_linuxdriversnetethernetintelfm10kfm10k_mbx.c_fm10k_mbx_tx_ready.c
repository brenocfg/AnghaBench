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
struct fm10k_mbx_info {scalar_t__ state; int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 scalar_t__ FM10K_STATE_OPEN ; 
 scalar_t__ fm10k_fifo_unused (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fm10k_mbx_tx_ready(struct fm10k_mbx_info *mbx, u16 len)
{
	u16 fifo_unused = fm10k_fifo_unused(&mbx->tx);

	return (mbx->state == FM10K_STATE_OPEN) && (fifo_unused >= len);
}