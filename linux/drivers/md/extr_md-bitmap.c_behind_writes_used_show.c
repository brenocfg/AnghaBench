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
struct mddev {int /*<<< orphan*/  lock; TYPE_1__* bitmap; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  behind_writes_used; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static ssize_t
behind_writes_used_show(struct mddev *mddev, char *page)
{
	ssize_t ret;
	spin_lock(&mddev->lock);
	if (mddev->bitmap == NULL)
		ret = sprintf(page, "0\n");
	else
		ret = sprintf(page, "%lu\n",
			      mddev->bitmap->behind_writes_used);
	spin_unlock(&mddev->lock);
	return ret;
}