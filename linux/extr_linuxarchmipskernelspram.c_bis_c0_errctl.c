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
 unsigned int read_c0_errctl () ; 
 int /*<<< orphan*/  write_c0_errctl (unsigned int) ; 

__attribute__((used)) static unsigned int bis_c0_errctl(unsigned int set)
{
	unsigned int res;
	res = read_c0_errctl();
	write_c0_errctl(res | set);
	return res;
}