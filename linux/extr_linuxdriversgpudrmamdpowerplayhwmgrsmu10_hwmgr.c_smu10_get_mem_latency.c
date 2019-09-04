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
typedef  scalar_t__ uint32_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 scalar_t__ MEM_FREQ_HIGH_LATENCY ; 
 scalar_t__ MEM_FREQ_LOW_LATENCY ; 
 scalar_t__ MEM_LATENCY_ERR ; 
 scalar_t__ MEM_LATENCY_HIGH ; 
 scalar_t__ MEM_LATENCY_LOW ; 

__attribute__((used)) static uint32_t smu10_get_mem_latency(struct pp_hwmgr *hwmgr,
		uint32_t clock)
{
	if (clock >= MEM_FREQ_LOW_LATENCY &&
			clock < MEM_FREQ_HIGH_LATENCY)
		return MEM_LATENCY_HIGH;
	else if (clock >= MEM_FREQ_HIGH_LATENCY)
		return MEM_LATENCY_LOW;
	else
		return MEM_LATENCY_ERR;
}