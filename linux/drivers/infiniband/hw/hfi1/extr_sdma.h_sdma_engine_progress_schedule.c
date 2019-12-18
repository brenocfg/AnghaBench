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
struct sdma_engine {int descq_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  _sdma_engine_progress_schedule (struct sdma_engine*) ; 
 int sdma_descq_inprocess (struct sdma_engine*) ; 

__attribute__((used)) static inline void sdma_engine_progress_schedule(
	struct sdma_engine *sde)
{
	if (!sde || sdma_descq_inprocess(sde) < (sde->descq_cnt / 8))
		return;
	_sdma_engine_progress_schedule(sde);
}