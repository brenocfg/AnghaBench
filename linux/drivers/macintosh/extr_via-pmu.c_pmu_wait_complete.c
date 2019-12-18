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
struct adb_request {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 scalar_t__ idle ; 
 scalar_t__ locked ; 
 scalar_t__ pmu_state ; 
 scalar_t__ uninitialized ; 
 int /*<<< orphan*/  via_pmu_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
pmu_wait_complete(struct adb_request *req)
{
	if (pmu_state == uninitialized)
		return;
	while((pmu_state != idle && pmu_state != locked) || !req->complete)
		via_pmu_interrupt(0, NULL);
}