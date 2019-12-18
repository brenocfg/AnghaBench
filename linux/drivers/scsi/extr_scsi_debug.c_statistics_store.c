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
 int /*<<< orphan*/  clear_queue_stats () ; 
 int sdebug_statistics ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static ssize_t statistics_store(struct device_driver *ddp, const char *buf,
				size_t count)
{
	int n;

	if ((count > 0) && (sscanf(buf, "%d", &n) == 1) && (n >= 0)) {
		if (n > 0)
			sdebug_statistics = true;
		else {
			clear_queue_stats();
			sdebug_statistics = false;
		}
		return count;
	}
	return -EINVAL;
}