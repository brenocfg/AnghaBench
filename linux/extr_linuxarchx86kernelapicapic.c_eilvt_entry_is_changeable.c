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
 unsigned int APIC_EILVT_MASKED ; 

__attribute__((used)) static inline int eilvt_entry_is_changeable(unsigned int old, unsigned int new)
{
	return (old & APIC_EILVT_MASKED)
		|| (new == APIC_EILVT_MASKED)
		|| ((new & ~APIC_EILVT_MASKED) == old);
}