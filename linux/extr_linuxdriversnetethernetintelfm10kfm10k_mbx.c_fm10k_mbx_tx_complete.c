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
struct fm10k_mbx_info {int /*<<< orphan*/  tx; } ;

/* Variables and functions */
 int fm10k_fifo_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fm10k_mbx_tx_complete(struct fm10k_mbx_info *mbx)
{
	return fm10k_fifo_empty(&mbx->tx);
}