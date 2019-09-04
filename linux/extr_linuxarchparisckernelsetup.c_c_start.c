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
struct seq_file {int dummy; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */

__attribute__((used)) static void *
c_start (struct seq_file *m, loff_t *pos)
{
    	/* Looks like the caller will call repeatedly until we return
	 * 0, signaling EOF perhaps.  This could be used to sequence
	 * through CPUs for example.  Since we print all cpu info in our
	 * show_cpuinfo() disregarding 'pos' (which I assume is 'v' above)
	 * we only allow for one "position".  */
	return ((long)*pos < 1) ? (void *)1 : NULL;
}