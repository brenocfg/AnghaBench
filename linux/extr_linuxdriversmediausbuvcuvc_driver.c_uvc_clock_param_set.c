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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EINVAL ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncasecmp (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uvc_clock_param ; 

__attribute__((used)) static int uvc_clock_param_set(const char *val, const struct kernel_param *kp)
{
	if (strncasecmp(val, "clock_", strlen("clock_")) == 0)
		val += strlen("clock_");

	if (strcasecmp(val, "monotonic") == 0)
		uvc_clock_param = CLOCK_MONOTONIC;
	else if (strcasecmp(val, "realtime") == 0)
		uvc_clock_param = CLOCK_REALTIME;
	else
		return -EINVAL;

	return 0;
}