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
 size_t PAGE_ALIGN (size_t) ; 
 size_t PAGE_SIZE ; 

size_t ttm_round_pot(size_t size)
{
	if ((size & (size - 1)) == 0)
		return size;
	else if (size > PAGE_SIZE)
		return PAGE_ALIGN(size);
	else {
		size_t tmp_size = 4;

		while (tmp_size < size)
			tmp_size <<= 1;

		return tmp_size;
	}
	return 0;
}