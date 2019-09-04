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
struct sysinfo_15_1_x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stsi (struct sysinfo_15_1_x*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topology_mnest_limit () ; 

void store_topology(struct sysinfo_15_1_x *info)
{
	stsi(info, 15, 1, topology_mnest_limit());
}