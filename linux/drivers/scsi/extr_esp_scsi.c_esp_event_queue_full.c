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
struct scsi_device {struct esp_lun_data* hostdata; } ;
struct esp_lun_data {scalar_t__ num_tagged; } ;
struct esp_cmd_entry {TYPE_1__* cmd; } ;
struct esp {int dummy; } ;
struct TYPE_2__ {struct scsi_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  scsi_track_queue_full (struct scsi_device*,scalar_t__) ; 

__attribute__((used)) static void esp_event_queue_full(struct esp *esp, struct esp_cmd_entry *ent)
{
	struct scsi_device *dev = ent->cmd->device;
	struct esp_lun_data *lp = dev->hostdata;

	scsi_track_queue_full(dev, lp->num_tagged - 1);
}