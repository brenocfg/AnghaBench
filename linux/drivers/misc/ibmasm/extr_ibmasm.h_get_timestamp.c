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

/* Variables and functions */
 int NSEC_PER_USEC ; 
 int /*<<< orphan*/  ktime_get_real_ts64 (struct timespec64*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long long,int) ; 

__attribute__((used)) static inline char *get_timestamp(char *buf)
{
	struct timespec64 now;

	ktime_get_real_ts64(&now);
	sprintf(buf, "%llu.%.08lu", (long long)now.tv_sec,
				now.tv_nsec / NSEC_PER_USEC);
	return buf;
}