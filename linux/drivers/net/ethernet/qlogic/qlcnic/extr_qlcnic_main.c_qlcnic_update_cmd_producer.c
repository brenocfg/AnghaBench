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
struct qlcnic_host_tx_ring {int /*<<< orphan*/  crb_cmd_producer; int /*<<< orphan*/  producer; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

inline void qlcnic_update_cmd_producer(struct qlcnic_host_tx_ring *tx_ring)
{
	writel(tx_ring->producer, tx_ring->crb_cmd_producer);
}