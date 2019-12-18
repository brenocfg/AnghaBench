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
struct device_driver {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int NO_DEBUG ; 
 int debugging ; 

__attribute__((used)) static ssize_t debug_flag_store(struct device_driver *ddp,
	const char *buf, size_t count)
{
/* We only care what the first byte of the data is the rest is unused.
 * if it's a '1' we turn on debug and if it's a '0' we disable it. All
 * other values have -EINVAL returned if they are passed in.
 */
	if (count > 0) {
		if (buf[0] == '0') {
			debugging = NO_DEBUG;
			return count;
		} else if (buf[0] == '1') {
			debugging = 1;
			return count;
		}
	}
	return -EINVAL;
}