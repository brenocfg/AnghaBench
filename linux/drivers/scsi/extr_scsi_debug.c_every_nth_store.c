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
 int /*<<< orphan*/  pr_info (char*) ; 
 int sdebug_every_nth ; 
 int sdebug_statistics ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  tweak_cmnd_count () ; 

__attribute__((used)) static ssize_t every_nth_store(struct device_driver *ddp, const char *buf,
			       size_t count)
{
	int nth;

	if ((count > 0) && (1 == sscanf(buf, "%d", &nth))) {
		sdebug_every_nth = nth;
		if (nth && !sdebug_statistics) {
			pr_info("every_nth needs statistics=1, set it\n");
			sdebug_statistics = true;
		}
		tweak_cmnd_count();
		return count;
	}
	return -EINVAL;
}