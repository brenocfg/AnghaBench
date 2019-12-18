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
struct scsi_cmnd {TYPE_1__* device; } ;
struct MPT3SAS_ADAPTER {scalar_t__ remove_host; scalar_t__ is_driver_loading; } ;
struct TYPE_2__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int FAILED ; 
 int /*<<< orphan*/  FORCE_BIG_HAMMER ; 
 int SUCCESS ; 
 int /*<<< orphan*/  ioc_info (struct MPT3SAS_ADAPTER*,char*,...) ; 
 int mpt3sas_base_hard_reset_handler (struct MPT3SAS_ADAPTER*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_print_command (struct scsi_cmnd*) ; 
 struct MPT3SAS_ADAPTER* shost_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
scsih_host_reset(struct scsi_cmnd *scmd)
{
	struct MPT3SAS_ADAPTER *ioc = shost_priv(scmd->device->host);
	int r, retval;

	ioc_info(ioc, "attempting host reset! scmd(%p)\n", scmd);
	scsi_print_command(scmd);

	if (ioc->is_driver_loading || ioc->remove_host) {
		ioc_info(ioc, "Blocking the host reset\n");
		r = FAILED;
		goto out;
	}

	retval = mpt3sas_base_hard_reset_handler(ioc, FORCE_BIG_HAMMER);
	r = (retval < 0) ? FAILED : SUCCESS;
out:
	ioc_info(ioc, "host reset: %s scmd(%p)\n",
		 r == SUCCESS ? "SUCCESS" : "FAILED", scmd);

	return r;
}