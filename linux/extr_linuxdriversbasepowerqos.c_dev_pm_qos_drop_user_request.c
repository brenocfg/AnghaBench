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
struct device {int dummy; } ;
typedef  enum dev_pm_qos_req_type { ____Placeholder_dev_pm_qos_req_type } dev_pm_qos_req_type ;

/* Variables and functions */
 int /*<<< orphan*/  __dev_pm_qos_drop_user_request (struct device*,int) ; 
 int /*<<< orphan*/  dev_pm_qos_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dev_pm_qos_drop_user_request(struct device *dev,
					 enum dev_pm_qos_req_type type)
{
	mutex_lock(&dev_pm_qos_mtx);
	__dev_pm_qos_drop_user_request(dev, type);
	mutex_unlock(&dev_pm_qos_mtx);
}