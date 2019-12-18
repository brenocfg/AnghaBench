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
 int /*<<< orphan*/  SOURCE_CHARGE ; 
 int /*<<< orphan*/  SOURCE_ENERGY ; 
 int /*<<< orphan*/  SOURCE_VOLTAGE ; 
 int do_calculate_time (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int calculate_time(int status)
{
	int time;

	time = do_calculate_time(status, SOURCE_ENERGY);
	if (time != -1)
		return time;

	time = do_calculate_time(status, SOURCE_CHARGE);
	if (time != -1)
		return time;

	time = do_calculate_time(status, SOURCE_VOLTAGE);
	if (time != -1)
		return time;

	return -1;
}