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
 int cycle_time ; 

__attribute__((used)) static int to_cycles(int ns)
{
    if (ns < 14)
	return 0;
    else
	return 2*(ns-14)/cycle_time;
}