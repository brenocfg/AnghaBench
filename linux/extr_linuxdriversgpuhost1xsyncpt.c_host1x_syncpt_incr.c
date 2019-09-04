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
struct host1x_syncpt {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int host1x_hw_syncpt_cpu_incr (int /*<<< orphan*/ ,struct host1x_syncpt*) ; 

int host1x_syncpt_incr(struct host1x_syncpt *sp)
{
	return host1x_hw_syncpt_cpu_incr(sp->host, sp);
}