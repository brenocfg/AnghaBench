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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  event_get_counter_info_version (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_length (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_offset (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_request (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_secondary_index (struct perf_event*) ; 
 int /*<<< orphan*/  event_get_starting_index (struct perf_event*) ; 
 unsigned long single_gpci_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 h_gpci_get_value(struct perf_event *event)
{
	u64 count;
	unsigned long ret = single_gpci_request(event_get_request(event),
					event_get_starting_index(event),
					event_get_secondary_index(event),
					event_get_counter_info_version(event),
					event_get_offset(event),
					event_get_length(event),
					&count);
	if (ret)
		return 0;
	return count;
}