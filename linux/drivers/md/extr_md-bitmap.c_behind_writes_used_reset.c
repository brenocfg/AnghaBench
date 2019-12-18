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
struct mddev {TYPE_1__* bitmap; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ behind_writes_used; } ;

/* Variables and functions */

__attribute__((used)) static ssize_t
behind_writes_used_reset(struct mddev *mddev, const char *buf, size_t len)
{
	if (mddev->bitmap)
		mddev->bitmap->behind_writes_used = 0;
	return len;
}