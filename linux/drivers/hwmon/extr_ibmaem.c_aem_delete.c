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
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
struct aem_data {int /*<<< orphan*/  id; int /*<<< orphan*/  pdev; TYPE_1__ ipmi; int /*<<< orphan*/  hwmon_dev; struct aem_data* rs_resp; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  aem_ida ; 
 int /*<<< orphan*/  aem_remove_sensors (struct aem_data*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_destroy_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct aem_data*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aem_delete(struct aem_data *data)
{
	list_del(&data->list);
	aem_remove_sensors(data);
	kfree(data->rs_resp);
	hwmon_device_unregister(data->hwmon_dev);
	ipmi_destroy_user(data->ipmi.user);
	platform_set_drvdata(data->pdev, NULL);
	platform_device_unregister(data->pdev);
	ida_simple_remove(&aem_ida, data->id);
	kfree(data);
}