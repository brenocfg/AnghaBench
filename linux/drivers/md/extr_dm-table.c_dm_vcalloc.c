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
 unsigned long ULONG_MAX ; 
 void* vzalloc (unsigned long) ; 

void *dm_vcalloc(unsigned long nmemb, unsigned long elem_size)
{
	unsigned long size;
	void *addr;

	/*
	 * Check that we're not going to overflow.
	 */
	if (nmemb > (ULONG_MAX / elem_size))
		return NULL;

	size = nmemb * elem_size;
	addr = vzalloc(size);

	return addr;
}