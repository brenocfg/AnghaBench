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
struct timespec64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xen_read_wallclock (struct timespec64*) ; 

__attribute__((used)) static void xen_get_wallclock(struct timespec64 *now)
{
	xen_read_wallclock(now);
}