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
struct mpic {int flags; } ;

/* Variables and functions */
 int MPIC_SECONDARY ; 
 unsigned int hard_smp_processor_id () ; 

__attribute__((used)) static inline unsigned int mpic_processor_id(struct mpic *mpic)
{
	unsigned int cpu = 0;

	if (!(mpic->flags & MPIC_SECONDARY))
		cpu = hard_smp_processor_id();

	return cpu;
}