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
struct mddev {TYPE_1__* bitmap; scalar_t__ degraded; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int need_sync; } ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EINVAL ; 
 size_t ENOENT ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static ssize_t can_clear_store(struct mddev *mddev, const char *buf, size_t len)
{
	if (mddev->bitmap == NULL)
		return -ENOENT;
	if (strncmp(buf, "false", 5) == 0)
		mddev->bitmap->need_sync = 1;
	else if (strncmp(buf, "true", 4) == 0) {
		if (mddev->degraded)
			return -EBUSY;
		mddev->bitmap->need_sync = 0;
	} else
		return -EINVAL;
	return len;
}