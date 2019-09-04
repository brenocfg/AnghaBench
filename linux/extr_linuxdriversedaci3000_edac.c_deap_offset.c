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
 int I3000_DEAP_GRAIN ; 
 int PAGE_MASK ; 

__attribute__((used)) static inline unsigned long deap_offset(u32 deap)
{
	return deap & ~(I3000_DEAP_GRAIN - 1) & ~PAGE_MASK;
}