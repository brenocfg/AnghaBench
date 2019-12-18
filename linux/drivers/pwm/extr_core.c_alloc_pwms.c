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

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOSPC ; 
 int MAX_PWMS ; 
 int /*<<< orphan*/  allocated_pwms ; 
 unsigned int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int alloc_pwms(int pwm, unsigned int count)
{
	unsigned int from = 0;
	unsigned int start;

	if (pwm >= MAX_PWMS)
		return -EINVAL;

	if (pwm >= 0)
		from = pwm;

	start = bitmap_find_next_zero_area(allocated_pwms, MAX_PWMS, from,
					   count, 0);

	if (pwm >= 0 && start != pwm)
		return -EEXIST;

	if (start + count > MAX_PWMS)
		return -ENOSPC;

	return start;
}