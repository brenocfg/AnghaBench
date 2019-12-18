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
struct mddev {long parallel_resync; scalar_t__ sync_thread; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 int /*<<< orphan*/  resync_wait ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
sync_force_parallel_store(struct mddev *mddev, const char *buf, size_t len)
{
	long n;

	if (kstrtol(buf, 10, &n))
		return -EINVAL;

	if (n != 0 && n != 1)
		return -EINVAL;

	mddev->parallel_resync = n;

	if (mddev->sync_thread)
		wake_up(&resync_wait);

	return len;
}