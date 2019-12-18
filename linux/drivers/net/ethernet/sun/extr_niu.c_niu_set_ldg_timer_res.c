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
struct niu {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LDG_TIMER_RES ; 
 int LDG_TIMER_RES_VAL ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_set_ldg_timer_res(struct niu *np, int res)
{
	if (res < 0 || res > LDG_TIMER_RES_VAL)
		return -EINVAL;


	nw64(LDG_TIMER_RES, res);

	return 0;
}