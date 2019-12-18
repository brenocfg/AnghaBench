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
struct rapl_package {int time_unit; } ;

/* Variables and functions */
 int div64_u64 (int,int) ; 

__attribute__((used)) static u64 rapl_compute_time_window_atom(struct rapl_package *rp, u64 value,
					 bool to_raw)
{
	/*
	 * Atom time unit encoding is straight forward val * time_unit,
	 * where time_unit is default to 1 sec. Never 0.
	 */
	if (!to_raw)
		return (value) ? value *= rp->time_unit : rp->time_unit;

	value = div64_u64(value, rp->time_unit);

	return value;
}