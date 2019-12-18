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
struct idle_inject_device {int /*<<< orphan*/  idle_duration_us; int /*<<< orphan*/  run_duration_us; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,unsigned int) ; 

void idle_inject_set_duration(struct idle_inject_device *ii_dev,
			      unsigned int run_duration_us,
			      unsigned int idle_duration_us)
{
	if (run_duration_us && idle_duration_us) {
		WRITE_ONCE(ii_dev->run_duration_us, run_duration_us);
		WRITE_ONCE(ii_dev->idle_duration_us, idle_duration_us);
	}
}