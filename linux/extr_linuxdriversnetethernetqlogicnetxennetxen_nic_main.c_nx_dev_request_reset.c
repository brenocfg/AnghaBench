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
typedef  scalar_t__ u32 ;
struct netxen_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NETXEN_FW_RESET_OWNER ; 
 scalar_t__ NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NX_CRB_DEV_STATE ; 
 scalar_t__ NX_DEV_FAILED ; 
 scalar_t__ NX_DEV_INITALIZING ; 
 scalar_t__ NX_DEV_NEED_AER ; 
 scalar_t__ NX_DEV_NEED_RESET ; 
 scalar_t__ netxen_api_lock (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_api_unlock (struct netxen_adapter*) ; 

int
nx_dev_request_reset(struct netxen_adapter *adapter)
{
	u32 state;
	int ret = -EINVAL;

	if (netxen_api_lock(adapter))
		return ret;

	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	if (state == NX_DEV_NEED_RESET || state == NX_DEV_FAILED)
		ret = 0;
	else if (state != NX_DEV_INITALIZING && state != NX_DEV_NEED_AER) {
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_NEED_RESET);
		adapter->flags |= NETXEN_FW_RESET_OWNER;
		ret = 0;
	}

	netxen_api_unlock(adapter);

	return ret;
}