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
struct pqi_scsi_dev {scalar_t__ is_physical_device; scalar_t__ wwid; int /*<<< orphan*/  volume_id; } ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool pqi_device_equal(struct pqi_scsi_dev *dev1,
	struct pqi_scsi_dev *dev2)
{
	if (dev1->is_physical_device != dev2->is_physical_device)
		return false;

	if (dev1->is_physical_device)
		return dev1->wwid == dev2->wwid;

	return memcmp(dev1->volume_id, dev2->volume_id,
		sizeof(dev1->volume_id)) == 0;
}