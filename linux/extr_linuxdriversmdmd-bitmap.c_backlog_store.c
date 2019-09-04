#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long max_write_behind; } ;
struct mddev {TYPE_1__ bitmap_info; } ;
typedef  int ssize_t ;

/* Variables and functions */
 unsigned long COUNTER_MAX ; 
 int EINVAL ; 
 int kstrtoul (char const*,int,unsigned long*) ; 

__attribute__((used)) static ssize_t
backlog_store(struct mddev *mddev, const char *buf, size_t len)
{
	unsigned long backlog;
	int rv = kstrtoul(buf, 10, &backlog);
	if (rv)
		return rv;
	if (backlog > COUNTER_MAX)
		return -EINVAL;
	mddev->bitmap_info.max_write_behind = backlog;
	return len;
}