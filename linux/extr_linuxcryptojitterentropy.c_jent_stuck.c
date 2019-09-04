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
struct rand_data {void* last_delta; int stuck; void* last_delta2; } ;
typedef  void* __u64 ;
typedef  void* __s64 ;

/* Variables and functions */

__attribute__((used)) static void jent_stuck(struct rand_data *ec, __u64 current_delta)
{
	__s64 delta2 = ec->last_delta - current_delta;
	__s64 delta3 = delta2 - ec->last_delta2;

	ec->last_delta = current_delta;
	ec->last_delta2 = delta2;

	if (!current_delta || !delta2 || !delta3)
		ec->stuck = 1;
}