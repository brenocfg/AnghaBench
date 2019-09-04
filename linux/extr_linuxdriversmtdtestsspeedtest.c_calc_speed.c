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
typedef  int uint64_t ;
struct TYPE_2__ {int erasesize; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (int,long) ; 
 int /*<<< orphan*/  finish ; 
 scalar_t__ goodebcnt ; 
 long ktime_ms_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* mtd ; 
 int /*<<< orphan*/  start ; 

__attribute__((used)) static long calc_speed(void)
{
	uint64_t k;
	long ms;

	ms = ktime_ms_delta(finish, start);
	if (ms == 0)
		return 0;
	k = (uint64_t)goodebcnt * (mtd->erasesize / 1024) * 1000;
	do_div(k, ms);
	return k;
}