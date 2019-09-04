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
struct mei_device {int minor; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEI_MAX_DEVS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct mei_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_idr ; 
 int /*<<< orphan*/  mei_minor_lock ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mei_minor_get(struct mei_device *dev)
{
	int ret;

	mutex_lock(&mei_minor_lock);
	ret = idr_alloc(&mei_idr, dev, 0, MEI_MAX_DEVS, GFP_KERNEL);
	if (ret >= 0)
		dev->minor = ret;
	else if (ret == -ENOSPC)
		dev_err(dev->dev, "too many mei devices\n");

	mutex_unlock(&mei_minor_lock);
	return ret;
}