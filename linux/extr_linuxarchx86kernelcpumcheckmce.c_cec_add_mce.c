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
struct mce {int addr; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  cec_add_elem (int) ; 
 scalar_t__ mce_is_correctable (struct mce*) ; 
 scalar_t__ mce_is_memory_error (struct mce*) ; 
 scalar_t__ mce_usable_address (struct mce*) ; 

__attribute__((used)) static bool cec_add_mce(struct mce *m)
{
	if (!m)
		return false;

	/* We eat only correctable DRAM errors with usable addresses. */
	if (mce_is_memory_error(m) &&
	    mce_is_correctable(m)  &&
	    mce_usable_address(m))
		if (!cec_add_elem(m->addr >> PAGE_SHIFT))
			return true;

	return false;
}