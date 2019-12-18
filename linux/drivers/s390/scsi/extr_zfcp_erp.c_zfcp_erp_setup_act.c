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
typedef  int u32 ;
struct zfcp_erp_action {int type; int status; scalar_t__ fsf_req_id; int /*<<< orphan*/  step; int /*<<< orphan*/  timer; int /*<<< orphan*/  list; struct zfcp_adapter* adapter; struct scsi_device* sdev; struct zfcp_port* port; } ;
struct zfcp_scsi_dev {int /*<<< orphan*/  status; struct zfcp_erp_action erp_action; } ;
struct zfcp_port {int /*<<< orphan*/  status; struct zfcp_erp_action erp_action; int /*<<< orphan*/  dev; } ;
struct zfcp_adapter {int /*<<< orphan*/  status; struct zfcp_erp_action erp_action; int /*<<< orphan*/  ref; } ;
struct scsi_device {int dummy; } ;
typedef  enum zfcp_erp_act_type { ____Placeholder_zfcp_erp_act_type } zfcp_erp_act_type ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  ZFCP_ERP_ACTION_REOPEN_ADAPTER 131 
#define  ZFCP_ERP_ACTION_REOPEN_LUN 130 
#define  ZFCP_ERP_ACTION_REOPEN_PORT 129 
#define  ZFCP_ERP_ACTION_REOPEN_PORT_FORCED 128 
 int /*<<< orphan*/  ZFCP_ERP_STEP_UNINITIALIZED ; 
 int /*<<< orphan*/  ZFCP_STATUS_COMMON_ERP_INUSE ; 
 int ZFCP_STATUS_COMMON_RUNNING ; 
 int ZFCP_STATUS_ERP_CLOSE_ONLY ; 
 int ZFCP_STATUS_ERP_NO_REF ; 
 int /*<<< orphan*/  atomic_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scsi_device_get (struct scsi_device*) ; 
 struct zfcp_scsi_dev* sdev_to_zfcp (struct scsi_device*) ; 
 int /*<<< orphan*/  zfcp_erp_action_dismiss_adapter (struct zfcp_adapter*) ; 
 int /*<<< orphan*/  zfcp_erp_action_dismiss_port (struct zfcp_port*) ; 

__attribute__((used)) static struct zfcp_erp_action *zfcp_erp_setup_act(enum zfcp_erp_act_type need,
						  u32 act_status,
						  struct zfcp_adapter *adapter,
						  struct zfcp_port *port,
						  struct scsi_device *sdev)
{
	struct zfcp_erp_action *erp_action;
	struct zfcp_scsi_dev *zfcp_sdev;

	if (WARN_ON_ONCE(need != ZFCP_ERP_ACTION_REOPEN_LUN &&
			 need != ZFCP_ERP_ACTION_REOPEN_PORT &&
			 need != ZFCP_ERP_ACTION_REOPEN_PORT_FORCED &&
			 need != ZFCP_ERP_ACTION_REOPEN_ADAPTER))
		return NULL;

	switch (need) {
	case ZFCP_ERP_ACTION_REOPEN_LUN:
		zfcp_sdev = sdev_to_zfcp(sdev);
		if (!(act_status & ZFCP_STATUS_ERP_NO_REF))
			if (scsi_device_get(sdev))
				return NULL;
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE,
				&zfcp_sdev->status);
		erp_action = &zfcp_sdev->erp_action;
		WARN_ON_ONCE(erp_action->port != port);
		WARN_ON_ONCE(erp_action->sdev != sdev);
		if (!(atomic_read(&zfcp_sdev->status) &
		      ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		break;

	case ZFCP_ERP_ACTION_REOPEN_PORT:
	case ZFCP_ERP_ACTION_REOPEN_PORT_FORCED:
		if (!get_device(&port->dev))
			return NULL;
		zfcp_erp_action_dismiss_port(port);
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE, &port->status);
		erp_action = &port->erp_action;
		WARN_ON_ONCE(erp_action->port != port);
		WARN_ON_ONCE(erp_action->sdev != NULL);
		if (!(atomic_read(&port->status) & ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		break;

	case ZFCP_ERP_ACTION_REOPEN_ADAPTER:
		kref_get(&adapter->ref);
		zfcp_erp_action_dismiss_adapter(adapter);
		atomic_or(ZFCP_STATUS_COMMON_ERP_INUSE, &adapter->status);
		erp_action = &adapter->erp_action;
		WARN_ON_ONCE(erp_action->port != NULL);
		WARN_ON_ONCE(erp_action->sdev != NULL);
		if (!(atomic_read(&adapter->status) &
		      ZFCP_STATUS_COMMON_RUNNING))
			act_status |= ZFCP_STATUS_ERP_CLOSE_ONLY;
		break;
	}

	WARN_ON_ONCE(erp_action->adapter != adapter);
	memset(&erp_action->list, 0, sizeof(erp_action->list));
	memset(&erp_action->timer, 0, sizeof(erp_action->timer));
	erp_action->step = ZFCP_ERP_STEP_UNINITIALIZED;
	erp_action->fsf_req_id = 0;
	erp_action->type = need;
	erp_action->status = act_status;

	return erp_action;
}