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
 int /*<<< orphan*/  _soft_restart (unsigned long,int) ; 
 int num_online_cpus () ; 

void soft_restart(unsigned long addr)
{
	_soft_restart(addr, num_online_cpus() == 1);
}