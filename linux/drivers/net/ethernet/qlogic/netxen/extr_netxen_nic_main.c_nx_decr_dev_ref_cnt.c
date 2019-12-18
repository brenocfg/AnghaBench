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
struct netxen_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int NXRD32 (struct netxen_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NXWR32 (struct netxen_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NX_CRB_DEV_REF_COUNT ; 
 int /*<<< orphan*/  NX_CRB_DEV_STATE ; 
 int NX_DEV_COLD ; 
 int NX_DEV_FAILED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ netxen_api_lock (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_api_unlock (struct netxen_adapter*) ; 

__attribute__((used)) static int
nx_decr_dev_ref_cnt(struct netxen_adapter *adapter)
{
	int count, state;
	if (netxen_api_lock(adapter))
		return -EIO;

	count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);
	WARN_ON(count == 0);

	NXWR32(adapter, NX_CRB_DEV_REF_COUNT, --count);
	state = NXRD32(adapter, NX_CRB_DEV_STATE);

	if (count == 0 && state != NX_DEV_FAILED)
		NXWR32(adapter, NX_CRB_DEV_STATE, NX_DEV_COLD);

	netxen_api_unlock(adapter);
	return count;
}