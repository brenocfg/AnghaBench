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
struct phy_device {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __phy_resume (struct phy_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int phy_resume(struct phy_device *phydev)
{
	int ret;

	mutex_lock(&phydev->lock);
	ret = __phy_resume(phydev);
	mutex_unlock(&phydev->lock);

	return ret;
}