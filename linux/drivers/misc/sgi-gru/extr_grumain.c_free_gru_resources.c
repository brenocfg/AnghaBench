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
struct gru_thread_state {int /*<<< orphan*/  ts_dsr_map; int /*<<< orphan*/  ts_cbr_map; } ;
struct gru_state {int /*<<< orphan*/  gs_dsr_map; int /*<<< orphan*/  gs_cbr_map; int /*<<< orphan*/  gs_active_contexts; } ;

/* Variables and functions */

__attribute__((used)) static void free_gru_resources(struct gru_state *gru,
			       struct gru_thread_state *gts)
{
	gru->gs_active_contexts--;
	gru->gs_cbr_map |= gts->ts_cbr_map;
	gru->gs_dsr_map |= gts->ts_dsr_map;
}