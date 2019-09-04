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
struct gru_state {int /*<<< orphan*/  gs_cbr_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  GRU_CBR_AU ; 
 unsigned long reserve_resources (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*) ; 

unsigned long gru_reserve_cb_resources(struct gru_state *gru, int cbr_au_count,
				       char *cbmap)
{
	return reserve_resources(&gru->gs_cbr_map, cbr_au_count, GRU_CBR_AU,
				 cbmap);
}