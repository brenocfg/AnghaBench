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
struct mlxsw_event_listener {scalar_t__ func; scalar_t__ trap_id; } ;

/* Variables and functions */

__attribute__((used)) static bool __is_event_listener_equal(const struct mlxsw_event_listener *el_a,
				      const struct mlxsw_event_listener *el_b)
{
	return (el_a->func == el_b->func &&
		el_a->trap_id == el_b->trap_id);
}