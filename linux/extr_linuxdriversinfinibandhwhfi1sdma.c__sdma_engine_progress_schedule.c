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
struct sdma_engine {int /*<<< orphan*/  progress_mask; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 scalar_t__ CCE_INT_FORCE ; 
 int IS_SDMA_START ; 
 int /*<<< orphan*/  trace_hfi1_sdma_engine_progress (struct sdma_engine*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void _sdma_engine_progress_schedule(
	struct sdma_engine *sde)
{
	trace_hfi1_sdma_engine_progress(sde, sde->progress_mask);
	/* assume we have selected a good cpu */
	write_csr(sde->dd,
		  CCE_INT_FORCE + (8 * (IS_SDMA_START / 64)),
		  sde->progress_mask);
}