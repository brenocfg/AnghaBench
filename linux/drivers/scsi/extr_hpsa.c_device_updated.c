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
struct hpsa_scsi_dev_t {scalar_t__ raid_level; scalar_t__ offload_config; scalar_t__ offload_to_be_enabled; scalar_t__ queue_depth; scalar_t__ ioaccel_handle; int /*<<< orphan*/  scsi3addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  is_logical_dev_addr_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int device_updated(struct hpsa_scsi_dev_t *dev1,
	struct hpsa_scsi_dev_t *dev2)
{
	/* Device attributes that can change, but don't mean
	 * that the device is a different device, nor that the OS
	 * needs to be told anything about the change.
	 */
	if (dev1->raid_level != dev2->raid_level)
		return 1;
	if (dev1->offload_config != dev2->offload_config)
		return 1;
	if (dev1->offload_to_be_enabled != dev2->offload_to_be_enabled)
		return 1;
	if (!is_logical_dev_addr_mode(dev1->scsi3addr))
		if (dev1->queue_depth != dev2->queue_depth)
			return 1;
	/*
	 * This can happen for dual domain devices. An active
	 * path change causes the ioaccel handle to change
	 *
	 * for example note the handle differences between p0 and p1
	 * Device                    WWN               ,WWN hash,Handle
	 * D016 p0|0x3 [02]P2E:01:01,0x5000C5005FC4DACA,0x9B5616,0x01030003
	 *	p1                   0x5000C5005FC4DAC9,0x6798C0,0x00040004
	 */
	if (dev1->ioaccel_handle != dev2->ioaccel_handle)
		return 1;
	return 0;
}