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
struct gru_thread_state {int ts_user_blade_id; int ts_user_chiplet_id; } ;
struct gru_state {int gs_blade_id; int gs_chiplet_id; } ;

/* Variables and functions */
 int uv_numa_blade_id () ; 

__attribute__((used)) static int gru_check_chiplet_assignment(struct gru_state *gru,
					struct gru_thread_state *gts)
{
	int blade_id;
	int chiplet_id;

	blade_id = gts->ts_user_blade_id;
	if (blade_id < 0)
		blade_id = uv_numa_blade_id();

	chiplet_id = gts->ts_user_chiplet_id;
	return gru->gs_blade_id == blade_id &&
		(chiplet_id < 0 || chiplet_id == gru->gs_chiplet_id);
}