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
struct pqi_scsi_dev {int /*<<< orphan*/ * sdev; int /*<<< orphan*/ * sas_port; scalar_t__ is_expander_smp_device; } ;

/* Variables and functions */

__attribute__((used)) static inline bool pqi_is_device_added(struct pqi_scsi_dev *device)
{
	if (device->is_expander_smp_device)
		return device->sas_port != NULL;

	return device->sdev != NULL;
}