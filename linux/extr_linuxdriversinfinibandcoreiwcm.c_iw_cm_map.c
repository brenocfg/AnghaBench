#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iwpm_sa_data {int /*<<< orphan*/  mapped_rem_addr; int /*<<< orphan*/  mapped_loc_addr; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; } ;
struct iwpm_dev_data {int /*<<< orphan*/  if_name; int /*<<< orphan*/  dev_name; } ;
struct iw_cm_id {int mapped; int /*<<< orphan*/  m_local_addr; int /*<<< orphan*/  local_addr; int /*<<< orphan*/  m_remote_addr; int /*<<< orphan*/  remote_addr; TYPE_2__* device; } ;
struct TYPE_4__ {TYPE_1__* iwcm; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_NL_IWCM ; 
 int /*<<< orphan*/  iw_cm_check_wildcard (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int iwpm_add_and_query_mapping (struct iwpm_sa_data*,int /*<<< orphan*/ ) ; 
 int iwpm_add_mapping (struct iwpm_sa_data*,int /*<<< orphan*/ ) ; 
 int iwpm_create_mapinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ iwpm_register_pid (struct iwpm_dev_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwpm_valid_pid () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iw_cm_map(struct iw_cm_id *cm_id, bool active)
{
	struct iwpm_dev_data pm_reg_msg;
	struct iwpm_sa_data pm_msg;
	int status;

	cm_id->m_local_addr = cm_id->local_addr;
	cm_id->m_remote_addr = cm_id->remote_addr;

	memcpy(pm_reg_msg.dev_name, cm_id->device->name,
	       sizeof(pm_reg_msg.dev_name));
	memcpy(pm_reg_msg.if_name, cm_id->device->iwcm->ifname,
	       sizeof(pm_reg_msg.if_name));

	if (iwpm_register_pid(&pm_reg_msg, RDMA_NL_IWCM) ||
	    !iwpm_valid_pid())
		return 0;

	cm_id->mapped = true;
	pm_msg.loc_addr = cm_id->local_addr;
	pm_msg.rem_addr = cm_id->remote_addr;
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
				   RDMA_NL_IWCM);
}