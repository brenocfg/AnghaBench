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
typedef  int /*<<< orphan*/  u64 ;
struct perf_event {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int /*<<< orphan*/  local64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void perf_event_count_update(struct perf_event *event, u64 count)
{
	local64_add(count, &event->count);
}