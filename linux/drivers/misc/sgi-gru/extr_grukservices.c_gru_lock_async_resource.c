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
struct gru_blade_state {void* kernel_dsr; void* kernel_cb; } ;

/* Variables and functions */
 int ASYNC_HAN_TO_BID (unsigned long) ; 
 struct gru_blade_state* ASYNC_HAN_TO_BS (unsigned long) ; 
 int GRU_HANDLE_STRIDE ; 
 int GRU_NUM_KERNEL_DSR_BYTES ; 
 int /*<<< orphan*/  gru_lock_kernel_context (int) ; 
 int uv_blade_nr_possible_cpus (int) ; 

void gru_lock_async_resource(unsigned long han,  void **cb, void **dsr)
{
	struct gru_blade_state *bs = ASYNC_HAN_TO_BS(han);
	int blade_id = ASYNC_HAN_TO_BID(han);
	int ncpus;

	gru_lock_kernel_context(blade_id);
	ncpus = uv_blade_nr_possible_cpus(blade_id);
	if (cb)
		*cb = bs->kernel_cb + ncpus * GRU_HANDLE_STRIDE;
	if (dsr)
		*dsr = bs->kernel_dsr + ncpus * GRU_NUM_KERNEL_DSR_BYTES;
}