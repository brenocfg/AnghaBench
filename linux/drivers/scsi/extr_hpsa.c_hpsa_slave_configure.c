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
struct scsi_device {int no_uld_attach; TYPE_1__* host; int /*<<< orphan*/  request_queue; int /*<<< orphan*/  eh_timeout; struct hpsa_scsi_dev_t* hostdata; } ;
struct hpsa_scsi_dev_t {int queue_depth; scalar_t__ external; scalar_t__ was_removed; int /*<<< orphan*/  expose_device; } ;
struct TYPE_2__ {int can_queue; } ;

/* Variables and functions */
 int EXTERNAL_QD ; 
 int /*<<< orphan*/  HPSA_EH_PTRAID_TIMEOUT ; 
 int /*<<< orphan*/  blk_queue_rq_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_change_queue_depth (struct scsi_device*,int) ; 

__attribute__((used)) static int hpsa_slave_configure(struct scsi_device *sdev)
{
	struct hpsa_scsi_dev_t *sd;
	int queue_depth;

	sd = sdev->hostdata;
	sdev->no_uld_attach = !sd || !sd->expose_device;

	if (sd) {
		sd->was_removed = 0;
		if (sd->external) {
			queue_depth = EXTERNAL_QD;
			sdev->eh_timeout = HPSA_EH_PTRAID_TIMEOUT;
			blk_queue_rq_timeout(sdev->request_queue,
						HPSA_EH_PTRAID_TIMEOUT);
		} else {
			queue_depth = sd->queue_depth != 0 ?
					sd->queue_depth : sdev->host->can_queue;
		}
	} else
		queue_depth = sdev->host->can_queue;

	scsi_change_queue_depth(sdev, queue_depth);

	return 0;
}