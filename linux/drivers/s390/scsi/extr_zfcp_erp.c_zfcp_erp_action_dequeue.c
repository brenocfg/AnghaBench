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
struct zfcp_scsi_dev {int /*<<< orphan*/  status; } ;
struct zfcp_erp_action {int status; int type; struct zfcp_adapter* adapter; TYPE_1__* port; int /*<<< orphan*/  sdev; int /*<<< orphan*/  list; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; int /*<<< orphan*/  erp_low_mem_count; int /*<<< orphan*/  erp_total_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_INUSE ; 
 int ZFCP_STATUS_ERP_LOWMEM ; 
 int /*<<< orphan*/  atomic_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfcp_dbf_rec_run (char*,struct zfcp_erp_action*) ; 

__attribute__((used)) static void zfcp_erp_action_dequeue(struct zfcp_erp_action *erp_action)
{
	struct zfcp_adapter *adapter = erp_action->adapter;
	struct zfcp_scsi_dev *zfcp_sdev;

	adapter->erp_total_count--;
	if (erp_action->status & ZFCP_STATUS_ERP_LOWMEM) {
		adapter->erp_low_mem_count--;
		erp_action->status &= ~ZFCP_STATUS_ERP_LOWMEM;
	}

	list_del(&erp_action->list);
	zfcp_dbf_rec_run("eractd1", erp_action);

	switch (erp_action->type) {
	case ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(erp_action->sdev);
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &zfcp_sdev->status);
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
	case ZFCP_ERP_ACTION_REOPEN_PORT:
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->port->status);
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		atomic_andnot(ZFCP_STATUS_COMMON_ERP_INUSE,
				  &erp_action->adapter->status);
		break;
	}
}