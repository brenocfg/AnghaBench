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
 scalar_t__ netxen_api_lock (struct netxen_adapter*) ; 
 int /*<<< orphan*/  netxen_api_unlock (struct netxen_adapter*) ; 

__attribute__((used)) static int
nx_incr_dev_ref_cnt(struct netxen_adapter *adapter)
{
	int count;
	if (netxen_api_lock(adapter))
		return -EIO;

	count = NXRD32(adapter, NX_CRB_DEV_REF_COUNT);

	NXWR32(adapter, NX_CRB_DEV_REF_COUNT, ++count);

	netxen_api_unlock(adapter);
	return count;
}