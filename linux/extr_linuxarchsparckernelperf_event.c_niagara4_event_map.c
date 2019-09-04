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
struct perf_event_map {int dummy; } ;

/* Variables and functions */
 struct perf_event_map const* niagara4_perfmon_event_map ; 

__attribute__((used)) static const struct perf_event_map *niagara4_event_map(int event_id)
{
	return &niagara4_perfmon_event_map[event_id];
}