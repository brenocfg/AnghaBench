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
struct iwpm_sa_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  mapped_rem_addr; int /*<<< orphan*/  mapped_loc_addr; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; } ;
struct iwpm_dev_data {int /*<<< orphan*/  if_name; int /*<<< orphan*/  dev_name; } ;
struct iw_cm_id {int mapped; int /*<<< orphan*/  m_local_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  m_remote_addr; int /*<<< orphan*/  remote_addr; TYPE_1__* device; } ;
struct TYPE_2__ {char* iw_ifname; int iw_driver_flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IWPM_FLAGS_NO_PORT_MAP ; 
 int IW_F_NO_PORT_MAP ; 
 int /*<<< orphan*/  RDMA_NL_IWCM ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iw_cm_check_wildcard (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwpm_add_and_query_mapping (struct iwpm_sa_data*,int /*<<< orphan*/ ) ; 
 int iwpm_add_mapping (struct iwpm_sa_data*,int /*<<< orphan*/ ) ; 
 int iwpm_create_mapinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ iwpm_register_pid (struct iwpm_dev_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwpm_valid_pid () ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int iw_cm_map(struct iw_cm_id *cm_id, bool active)
{
	const char *devname = dev_name(&cm_id->device->dev);
	const char *ifname = cm_id->device->iw_ifname;
	struct iwpm_dev_data pm_reg_msg = {};
	struct iwpm_sa_data pm_msg;
	int status;

	if (strlen(devname) >= sizeof(pm_reg_msg.dev_name) ||
	    strlen(ifname) >= sizeof(pm_reg_msg.if_name))
		return -EINVAL;

	cm_id->m_local_addr = cm_id->local_addr;
	cm_id->m_remote_addr = cm_id->remote_addr;

	strcpy(pm_reg_msg.dev_name, devname);
	strcpy(pm_reg_msg.if_name, ifname);

	if (iwpm_register_pid(&pm_reg_msg, RDMA_NL_IWCM) ||
	    !iwpm_valid_pid())
		return 0;

	cm_id->mapped = true;
	pm_msg.loc_addr = cm_id->local_addr;
	pm_msg.rem_addr = cm_id->remote_addr;
	pm_msg.flags = (cm_id->device->iw_driver_flags & IW_F_NO_PORT_MAP) ?
		       IWPM_FLAGS_NO_PORT_MAP : 0;
	if (active)
		status = iwpm_add_and_query_mapping(&pm_msg,
						    RDMA_NL_IWCM);
	else
		status = iwpm_add_mapping(&pm_msg, RDMA_NL_IWCM);

	if (!status) {
		cm_id->m_local_addr = pm_msg.mapped_loc_addr;
		if (active) {
			cm_id->m_remote_addr = pm_msg.mapped_rem_addr;
			iw_cm_check_wildcard(&pm_msg.mapped_rem_addr,
					     &cm_id->remote_addr,
					     &cm_id->m_remote_addr);
		}
	}

	return iwpm_create_mapinfo(&cm_id->local_addr,
				   &cm_id->m_local_addr,
				   RDMA_NL_IWCM, pm_msg.flags);
}