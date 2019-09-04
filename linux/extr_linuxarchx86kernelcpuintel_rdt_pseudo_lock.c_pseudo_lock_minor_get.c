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
 int ENOSPC ; 
 unsigned long MINORBITS ; 
 int /*<<< orphan*/  __clear_bit (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long find_first_bit (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pseudo_lock_minor_avail ; 

__attribute__((used)) static int pseudo_lock_minor_get(unsigned int *minor)
{
	unsigned long first_bit;

	first_bit = find_first_bit(&pseudo_lock_minor_avail, MINORBITS);

	if (first_bit == MINORBITS)
		return -ENOSPC;

	__clear_bit(first_bit, &pseudo_lock_minor_avail);
	*minor = first_bit;

	return 0;
}