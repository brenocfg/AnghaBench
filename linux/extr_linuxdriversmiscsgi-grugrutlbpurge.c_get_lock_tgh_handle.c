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
struct gru_tlb_global_handle {int dummy; } ;
struct gru_state {scalar_t__ gs_blade_id; } ;

/* Variables and functions */
 int get_off_blade_tgh (struct gru_state*) ; 
 int get_on_blade_tgh (struct gru_state*) ; 
 struct gru_tlb_global_handle* get_tgh_by_index (struct gru_state*,int) ; 
 int /*<<< orphan*/  lock_tgh_handle (struct gru_tlb_global_handle*) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 scalar_t__ uv_numa_blade_id () ; 

__attribute__((used)) static struct gru_tlb_global_handle *get_lock_tgh_handle(struct gru_state
							 *gru)
{
	struct gru_tlb_global_handle *tgh;
	int n;

	preempt_disable();
	if (uv_numa_blade_id() == gru->gs_blade_id)
		n = get_on_blade_tgh(gru);
	else
		n = get_off_blade_tgh(gru);
	tgh = get_tgh_by_index(gru, n);
	lock_tgh_handle(tgh);

	return tgh;
}