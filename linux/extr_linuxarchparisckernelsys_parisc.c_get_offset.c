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
 unsigned int PAGE_SHIFT ; 
 int SHM_COLOUR ; 

__attribute__((used)) static int get_offset(unsigned int last_mmap)
{
	return (last_mmap & (SHM_COLOUR-1)) >> PAGE_SHIFT;
}