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
struct scsi_device {TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_wait; } ;

/* Variables and functions */
 int scsi_device_online (struct scsi_device*) ; 
 int /*<<< orphan*/  scsi_host_in_recovery (TYPE_1__*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

int scsi_block_when_processing_errors(struct scsi_device *sdev)
{
	int online;

	wait_event(sdev->host->host_wait, !scsi_host_in_recovery(sdev->host));

	online = scsi_device_online(sdev);

	return online;
}