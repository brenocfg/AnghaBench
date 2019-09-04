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

/* Variables and functions */
 unsigned int NMI_MAX_COUNTER_BITS ; 
 int /*<<< orphan*/  evntsel_nmi_owner ; 
 unsigned int nmi_evntsel_msr_to_bit (unsigned int) ; 
 int /*<<< orphan*/  test_and_set_bit (unsigned int,int /*<<< orphan*/ ) ; 

int reserve_evntsel_nmi(unsigned int msr)
{
	unsigned int counter;

	counter = nmi_evntsel_msr_to_bit(msr);
	/* register not managed by the allocator? */
	if (counter > NMI_MAX_COUNTER_BITS)
		return 1;

	if (!test_and_set_bit(counter, evntsel_nmi_owner))
		return 1;
	return 0;
}