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
struct dc_context {int dummy; } ;

/* Variables and functions */

unsigned long long dm_get_elapse_time_in_ns(struct dc_context *ctx,
		unsigned long long current_time_stamp,
		unsigned long long last_time_stamp)
{
	return current_time_stamp - last_time_stamp;
}