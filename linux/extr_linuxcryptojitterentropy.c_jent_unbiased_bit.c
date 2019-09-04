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
struct rand_data {int dummy; } ;
typedef  int __u64 ;

/* Variables and functions */
 int jent_measure_jitter (struct rand_data*) ; 

__attribute__((used)) static __u64 jent_unbiased_bit(struct rand_data *entropy_collector)
{
	do {
		__u64 a = jent_measure_jitter(entropy_collector);
		__u64 b = jent_measure_jitter(entropy_collector);

		if (a == b)
			continue;
		if (1 == a)
			return 1;
		else
			return 0;
	} while (1);
}