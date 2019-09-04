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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dpu_power_handle {int /*<<< orphan*/  phandle_lock; int /*<<< orphan*/  event_list; int /*<<< orphan*/  power_client_clist; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void dpu_power_resource_init(struct platform_device *pdev,
	struct dpu_power_handle *phandle)
{
	phandle->dev = &pdev->dev;

	INIT_LIST_HEAD(&phandle->power_client_clist);
	INIT_LIST_HEAD(&phandle->event_list);

	mutex_init(&phandle->phandle_lock);
}