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
struct pqi_scsi_dev {int /*<<< orphan*/  devtype; scalar_t__ is_expander_smp_device; } ;

/* Variables and functions */
 char const* scsi_device_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline const char *pqi_device_type(struct pqi_scsi_dev *device)
{
	if (device->is_expander_smp_device)
		return "Enclosure SMP    ";

	return scsi_device_type(device->devtype);
}