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
struct scsi_device {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; TYPE_1__* host; } ;
struct DeviceCtlBlk {int dummy; } ;
struct AdapterCtlBlk {int dummy; } ;
struct TYPE_2__ {scalar_t__ hostdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_remove_and_free_device (struct AdapterCtlBlk*,struct DeviceCtlBlk*) ; 
 struct DeviceCtlBlk* find_dcb (struct AdapterCtlBlk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dc395x_slave_destroy(struct scsi_device *scsi_device)
{
	struct AdapterCtlBlk *acb = (struct AdapterCtlBlk *)scsi_device->host->hostdata;
	struct DeviceCtlBlk *dcb = find_dcb(acb, scsi_device->id, scsi_device->lun);
	if (dcb)
		adapter_remove_and_free_device(acb, dcb);
}