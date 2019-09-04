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
typedef  int uint32_t ;
typedef  int u32 ;

/* Variables and functions */
 int MSR_F15H_PERF_CTL ; 
 int MSR_F15H_PERF_CTR ; 
#define  MSR_K7_EVNTSEL0 135 
#define  MSR_K7_EVNTSEL1 134 
#define  MSR_K7_EVNTSEL2 133 
#define  MSR_K7_EVNTSEL3 132 
#define  MSR_K7_PERFCTR0 131 
#define  MSR_K7_PERFCTR1 130 
#define  MSR_K7_PERFCTR2 129 
#define  MSR_K7_PERFCTR3 128 

__attribute__((used)) static inline uint32_t get_fam15h_addr(u32 addr)
{
	switch (addr) {
	case MSR_K7_PERFCTR0:
	case MSR_K7_PERFCTR1:
	case MSR_K7_PERFCTR2:
	case MSR_K7_PERFCTR3:
		return MSR_F15H_PERF_CTR + (addr - MSR_K7_PERFCTR0);
	case MSR_K7_EVNTSEL0:
	case MSR_K7_EVNTSEL1:
	case MSR_K7_EVNTSEL2:
	case MSR_K7_EVNTSEL3:
		return MSR_F15H_PERF_CTL + (addr - MSR_K7_EVNTSEL0);
	default:
		break;
	}

	return addr;
}