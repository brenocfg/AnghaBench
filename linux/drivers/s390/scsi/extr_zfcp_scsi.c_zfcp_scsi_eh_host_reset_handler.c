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
struct zfcp_scsi_dev {TYPE_1__* port; } ;
struct zfcp_adapter {int connection_features; } ;
struct scsi_cmnd {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {struct zfcp_adapter* adapter; } ;

/* Variables and functions */
 int FSF_FEATURE_NPIV_MODE ; 
 int SUCCESS ; 
 int fc_block_scsi_eh (struct scsi_cmnd*) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_scsi_eh (char*,struct zfcp_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfcp_erp_adapter_reopen (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_port_forced_reopen_all (struct zfcp_adapter*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zfcp_erp_wait (struct zfcp_adapter*) ; 

__attribute__((used)) static int zfcp_scsi_eh_host_reset_handler(struct scsi_cmnd *scpnt)
{
	struct zfcp_scsi_dev *zfcp_sdev = sdev_to_zfcp(scpnt->device);
	struct zfcp_adapter *adapter = zfcp_sdev->port->adapter;
	int ret = SUCCESS, fc_ret;

	if (!(adapter->connection_features & FSF_FEATURE_NPIV_MODE)) {
		zfcp_erp_port_forced_reopen_all(adapter, 0, "schrh_p");
		zfcp_erp_wait(adapter);
	}
	zfcp_erp_adapter_reopen(adapter, 0, "schrh_1");
	zfcp_erp_wait(adapter);
	fc_ret = fc_block_scsi_eh(scpnt);
	if (fc_ret)
		ret = fc_ret;

	zfcp_dbf_scsi_eh("schrh_r", adapter, ~0, ret);
	return ret;
}