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
 scalar_t__ single_24x7_request (struct perf_event*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 h_24x7_get_value(struct perf_event *event)
{
	u64 ct;

	if (single_24x7_request(event, &ct))
		/* We checked this in event init, shouldn't fail here... */
		return 0;

	return ct;
}