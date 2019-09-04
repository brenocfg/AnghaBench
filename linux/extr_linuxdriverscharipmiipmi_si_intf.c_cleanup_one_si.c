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
struct smi_info {scalar_t__ pdev; scalar_t__ pdev_registered; scalar_t__ intf; int /*<<< orphan*/  link; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_unregister_smi (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct smi_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_put (scalar_t__) ; 
 int /*<<< orphan*/  platform_device_unregister (scalar_t__) ; 

__attribute__((used)) static void cleanup_one_si(struct smi_info *smi_info)
{
	if (!smi_info)
		return;

	list_del(&smi_info->link);

	if (smi_info->intf)
		ipmi_unregister_smi(smi_info->intf);

	if (smi_info->pdev) {
		if (smi_info->pdev_registered)
			platform_device_unregister(smi_info->pdev);
		else
			platform_device_put(smi_info->pdev);
	}

	kfree(smi_info);
}