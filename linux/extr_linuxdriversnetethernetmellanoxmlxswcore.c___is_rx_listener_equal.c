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
struct mlxsw_rx_listener {scalar_t__ func; scalar_t__ local_port; scalar_t__ trap_id; } ;

/* Variables and functions */

__attribute__((used)) static bool __is_rx_listener_equal(const struct mlxsw_rx_listener *rxl_a,
				   const struct mlxsw_rx_listener *rxl_b)
{
	return (rxl_a->func == rxl_b->func &&
		rxl_a->local_port == rxl_b->local_port &&
		rxl_a->trap_id == rxl_b->trap_id);
}