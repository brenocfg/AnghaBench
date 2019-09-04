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
typedef  int u64 ;
struct perf_event_attr {int config; int /*<<< orphan*/  config1; } ;
struct perf_event {struct perf_event_attr attr; } ;
struct hw_perf_event {int config; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned int PERF_COUNT_HW_CACHE_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_OP_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 unsigned int array_index_nospec (unsigned int,unsigned int) ; 
 int*** hw_cache_event_ids ; 
 int /*<<< orphan*/ *** hw_cache_extra_regs ; 
 int x86_pmu_extra_regs (int,struct perf_event*) ; 

__attribute__((used)) static inline int
set_ext_hw_attr(struct hw_perf_event *hwc, struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	unsigned int cache_type, cache_op, cache_result;
	u64 config, val;

	config = attr->config;

	cache_type = (config >> 0) & 0xff;
	if (cache_type >= PERF_COUNT_HW_CACHE_MAX)
		return -EINVAL;
	cache_type = array_index_nospec(cache_type, PERF_COUNT_HW_CACHE_MAX);

	cache_op = (config >>  8) & 0xff;
	if (cache_op >= PERF_COUNT_HW_CACHE_OP_MAX)
		return -EINVAL;
	cache_op = array_index_nospec(cache_op, PERF_COUNT_HW_CACHE_OP_MAX);

	cache_result = (config >> 16) & 0xff;
	if (cache_result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		return -EINVAL;
	cache_result = array_index_nospec(cache_result, PERF_COUNT_HW_CACHE_RESULT_MAX);

	val = hw_cache_event_ids[cache_type][cache_op][cache_result];

	if (val == 0)
		return -ENOENT;

	if (val == -1)
		return -EINVAL;

	hwc->config |= val;
	attr->config1 = hw_cache_extra_regs[cache_type][cache_op][cache_result];
	return x86_pmu_extra_regs(val, event);
}