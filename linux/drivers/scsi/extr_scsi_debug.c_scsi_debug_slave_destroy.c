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
struct sdebug_dev_info {int used; } ;
struct scsi_device {int /*<<< orphan*/ * hostdata; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; TYPE_1__* host; } ;
struct TYPE_2__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdebug_verbose ; 

__attribute__((used)) static void scsi_debug_slave_destroy(struct scsi_device *sdp)
{
	struct sdebug_dev_info *devip =
		(struct sdebug_dev_info *)sdp->hostdata;

	if (sdebug_verbose)
		pr_info("slave_destroy <%u %u %u %llu>\n",
		       sdp->host->host_no, sdp->channel, sdp->id, sdp->lun);
	if (devip) {
		/* make this slot available for re-use */
		devip->used = false;
		sdp->hostdata = NULL;
	}
}