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
 int EINVAL ; 
 scalar_t__ VERBOSE ; 
 scalar_t__ debug ; 
 int heartbeat ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 

__attribute__((used)) static int pcwd_set_heartbeat(int t)
{
	if (t < 2 || t > 7200) /* arbitrary upper limit */
		return -EINVAL;

	heartbeat = t;

	if (debug >= VERBOSE)
		pr_debug("New heartbeat: %d\n", heartbeat);

	return 0;
}