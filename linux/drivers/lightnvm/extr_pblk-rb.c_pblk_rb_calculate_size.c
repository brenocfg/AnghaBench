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
 unsigned int NVM_MAX_VLBA ; 
 int get_count_order (unsigned int) ; 
 int max (int,int) ; 

__attribute__((used)) static unsigned int pblk_rb_calculate_size(unsigned int nr_entries,
					   unsigned int threshold)
{
	unsigned int thr_sz = 1 << (get_count_order(threshold + NVM_MAX_VLBA));
	unsigned int max_sz = max(thr_sz, nr_entries);
	unsigned int max_io;

	/* Alloc a write buffer that can (i) fit at least two split bios
	 * (considering max I/O size NVM_MAX_VLBA, and (ii) guarantee that the
	 * threshold will be respected
	 */
	max_io = (1 << max((int)(get_count_order(max_sz)),
				(int)(get_count_order(NVM_MAX_VLBA << 1))));
	if ((threshold + NVM_MAX_VLBA) >= max_io)
		max_io <<= 1;

	return max_io;
}