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
struct timespec64 {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct date_time_t {int MilliSecond; int /*<<< orphan*/  Second; int /*<<< orphan*/  Minute; int /*<<< orphan*/  Hour; int /*<<< orphan*/  Day; scalar_t__ Month; scalar_t__ Year; } ;

/* Variables and functions */
 int NSEC_PER_MSEC ; 
 int /*<<< orphan*/  mktime64 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exfat_time_fat2unix(struct timespec64 *ts, struct date_time_t *tp)
{
	ts->tv_sec = mktime64(tp->Year + 1980, tp->Month + 1, tp->Day,
			      tp->Hour, tp->Minute, tp->Second);

	ts->tv_nsec = tp->MilliSecond * NSEC_PER_MSEC;
}