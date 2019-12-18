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
struct sdebug_dev_info {int dummy; } ;
struct scsi_device {int no_uld_attach; struct sdebug_dev_info* hostdata; TYPE_1__* host; int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; } ;
struct TYPE_2__ {scalar_t__ max_cmd_len; int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 scalar_t__ SDEBUG_MAX_CMD_LEN ; 
 int /*<<< orphan*/  config_cdb_len (struct scsi_device*) ; 
 struct sdebug_dev_info* find_build_dev_info (struct scsi_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sdebug_no_uld ; 
 scalar_t__ sdebug_verbose ; 

__attribute__((used)) static int scsi_debug_slave_configure(struct scsi_device *sdp)
{
	struct sdebug_dev_info *devip =
			(struct sdebug_dev_info *)sdp->hostdata;

	if (sdebug_verbose)
		pr_info("slave_configure <%u %u %u %llu>\n",
		       sdp->host->host_no, sdp->channel, sdp->id, sdp->lun);
	if (sdp->host->max_cmd_len != SDEBUG_MAX_CMD_LEN)
		sdp->host->max_cmd_len = SDEBUG_MAX_CMD_LEN;
	if (devip == NULL) {
		devip = find_build_dev_info(sdp);
		if (devip == NULL)
			return 1;  /* no resources, will be marked offline */
	}
	sdp->hostdata = devip;
	if (sdebug_no_uld)
		sdp->no_uld_attach = 1;
	config_cdb_len(sdp);
	return 0;
}