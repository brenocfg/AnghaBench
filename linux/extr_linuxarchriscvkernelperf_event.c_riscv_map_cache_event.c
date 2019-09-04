#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int**** cache_events; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 unsigned int PERF_COUNT_HW_CACHE_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_OP_MAX ; 
 unsigned int PERF_COUNT_HW_CACHE_RESULT_MAX ; 
 int RISCV_OP_UNSUPP ; 
 int riscv_map_cache_decode (int /*<<< orphan*/ ,unsigned int*,unsigned int*,unsigned int*) ; 
 TYPE_1__* riscv_pmu ; 

__attribute__((used)) static int riscv_map_cache_event(u64 config)
{
	unsigned int type, op, result;
	int err = -ENOENT;
		int code;

	err = riscv_map_cache_decode(config, &type, &op, &result);
	if (!riscv_pmu->cache_events || err)
		return err;

	if (type >= PERF_COUNT_HW_CACHE_MAX ||
	    op >= PERF_COUNT_HW_CACHE_OP_MAX ||
	    result >= PERF_COUNT_HW_CACHE_RESULT_MAX)
		return -EINVAL;

	code = (*riscv_pmu->cache_events)[type][op][result];
	if (code == RISCV_OP_UNSUPP)
		return -EINVAL;

	return code;
}