#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ smca; } ;

/* Variables and functions */
 TYPE_1__ mce_flags ; 

__attribute__((used)) static inline bool is_shared_bank(int bank)
{
	/*
	 * Scalable MCA provides for only one core to have access to the MSRs of
	 * a shared bank.
	 */
	if (mce_flags.smca)
		return false;

	/* Bank 4 is for northbridge reporting and is thus shared */
	return (bank == 4);
}