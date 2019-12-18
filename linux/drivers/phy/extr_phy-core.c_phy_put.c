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
struct phy {int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* release ) (struct phy*) ;} ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct phy*) ; 

void phy_put(struct phy *phy)
{
	if (!phy || IS_ERR(phy))
		return;

	mutex_lock(&phy->mutex);
	if (phy->ops->release)
		phy->ops->release(phy);
	mutex_unlock(&phy->mutex);

	module_put(phy->ops->owner);
	put_device(&phy->dev);
}