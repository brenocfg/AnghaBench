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
 unsigned long dma_find_base (unsigned int) ; 

__attribute__((used)) static unsigned long dma_base_addr(unsigned int chan)
{
	unsigned long base = dma_find_base(chan);

	/* Normalize offset calculation */
	if (chan >= 9)
		chan -= 6;
	if (chan >= 4)
		base += 0x10;

	return base + (chan * 0x10);
}