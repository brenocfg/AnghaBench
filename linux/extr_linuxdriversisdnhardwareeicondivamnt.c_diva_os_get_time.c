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
typedef  scalar_t__ dword ;

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  ktime_get_ts64 (struct timespec64*) ; 

void diva_os_get_time(dword *sec, dword *usec)
{
	struct timespec64 time;

	ktime_get_ts64(&time);

	*sec = (dword) time.tv_sec;
	*usec = (dword) (time.tv_nsec / NSEC_PER_USEC);
}