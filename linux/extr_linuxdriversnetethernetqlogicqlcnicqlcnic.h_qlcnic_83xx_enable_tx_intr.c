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
struct qlcnic_host_tx_ring {int /*<<< orphan*/  crb_intr_mask; } ;
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qlcnic_83xx_enable_tx_intr(struct qlcnic_adapter *adapter,
			   struct qlcnic_host_tx_ring *tx_ring)
{
	writel(0, tx_ring->crb_intr_mask);
}