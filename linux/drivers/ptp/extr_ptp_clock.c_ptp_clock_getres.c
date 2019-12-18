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
struct timespec64 {int tv_nsec; scalar_t__ tv_sec; } ;
struct posix_clock {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int ptp_clock_getres(struct posix_clock *pc, struct timespec64 *tp)
{
	tp->tv_sec = 0;
	tp->tv_nsec = 1;
	return 0;
}