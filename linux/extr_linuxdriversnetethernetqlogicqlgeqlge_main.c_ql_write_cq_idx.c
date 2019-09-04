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
struct rx_ring {int /*<<< orphan*/  cnsmr_idx_db_reg; int /*<<< orphan*/  cnsmr_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ql_write_db_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ql_write_cq_idx(struct rx_ring *rx_ring)
{
	ql_write_db_reg(rx_ring->cnsmr_idx, rx_ring->cnsmr_idx_db_reg);
}