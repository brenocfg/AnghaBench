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
 int find_closest (unsigned long,int const*,unsigned int) ; 

__attribute__((used)) static int FREQ_TO_REG(const int *map,
		       unsigned int map_size, unsigned long freq)
{
	return find_closest(freq, map, map_size);
}