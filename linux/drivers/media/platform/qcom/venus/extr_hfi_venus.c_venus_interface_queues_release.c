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
struct venus_hfi_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  sfr; int /*<<< orphan*/  ifaceq_table; int /*<<< orphan*/ * queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  venus_free (struct venus_hfi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void venus_interface_queues_release(struct venus_hfi_device *hdev)
{
	mutex_lock(&hdev->lock);

	venus_free(hdev, &hdev->ifaceq_table);
	venus_free(hdev, &hdev->sfr);

	memset(hdev->queues, 0, sizeof(hdev->queues));
	memset(&hdev->ifaceq_table, 0, sizeof(hdev->ifaceq_table));
	memset(&hdev->sfr, 0, sizeof(hdev->sfr));

	mutex_unlock(&hdev->lock);
}