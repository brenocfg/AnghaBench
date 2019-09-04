#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qxl_monitors_config {int dummy; } ;
struct qxl_head {int dummy; } ;
struct qxl_device {TYPE_1__* client_monitors_config; } ;
struct TYPE_3__ {unsigned int count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qxl_alloc_client_monitors_config(struct qxl_device *qdev, unsigned count)
{
	if (qdev->client_monitors_config &&
	    count > qdev->client_monitors_config->count) {
		kfree(qdev->client_monitors_config);
		qdev->client_monitors_config = NULL;
	}
	if (!qdev->client_monitors_config) {
		qdev->client_monitors_config = kzalloc(
				sizeof(struct qxl_monitors_config) +
				sizeof(struct qxl_head) * count, GFP_KERNEL);
		if (!qdev->client_monitors_config)
			return;
	}
	qdev->client_monitors_config->count = count;
}