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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ips_driver {int dummy; } ;

/* Variables and functions */
 int IPS_SAMPLE_COUNT ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 

__attribute__((used)) static u32 calc_avg_power(struct ips_driver *ips, u32 *array)
{
	u64 total = 0;
	u32 avg;
	int i;

	for (i = 0; i < IPS_SAMPLE_COUNT; i++)
		total += array[i];

	do_div(total, IPS_SAMPLE_COUNT);
	avg = (u32)total;

	return avg;
}