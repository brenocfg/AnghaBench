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
typedef  int u32 ;

/* Variables and functions */
 int RESET_A15_NCORERESET (unsigned int) ; 
 int RESET_A7_NCORERESET (unsigned int) ; 
 scalar_t__ RESET_CTRL ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ scc ; 

__attribute__((used)) static int tc2_core_in_reset(unsigned int cpu, unsigned int cluster)
{
	u32 mask = cluster ?
		  RESET_A7_NCORERESET(cpu)
		: RESET_A15_NCORERESET(cpu);

	return !(readl_relaxed(scc + RESET_CTRL) & mask);
}