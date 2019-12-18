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
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  epoch ; 
 scalar_t__ mktime64 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 
 int /*<<< orphan*/  write_elapsed_second (scalar_t__) ; 

__attribute__((used)) static int vr41xx_rtc_set_time(struct device *dev, struct rtc_time *time)
{
	time64_t epoch_sec, current_sec;

	epoch_sec = mktime64(epoch, 1, 1, 0, 0, 0);
	current_sec = rtc_tm_to_time64(time);

	write_elapsed_second(current_sec - epoch_sec);

	return 0;
}