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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int smp_length_check(u32 data_size, u32 request_len)
{
	if (unlikely(request_len < data_size))
		return -EINVAL;

	return 0;
}