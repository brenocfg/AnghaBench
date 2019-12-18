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
struct scsi_device {int dummy; } ;
typedef  enum scsi_device_state { ____Placeholder_scsi_device_state } scsi_device_state ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_internal_device_unblock (struct scsi_device*,int) ; 

__attribute__((used)) static void
device_unblock(struct scsi_device *sdev, void *data)
{
	scsi_internal_device_unblock(sdev, *(enum scsi_device_state *)data);
}