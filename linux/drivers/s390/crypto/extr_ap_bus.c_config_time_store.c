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
struct bus_type {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int HZ ; 
 int ap_config_time ; 
 int /*<<< orphan*/  ap_config_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t config_time_store(struct bus_type *bus,
				 const char *buf, size_t count)
{
	int time;

	if (sscanf(buf, "%d\n", &time) != 1 || time < 5 || time > 120)
		return -EINVAL;
	ap_config_time = time;
	mod_timer(&ap_config_timer, jiffies + ap_config_time * HZ);
	return count;
}