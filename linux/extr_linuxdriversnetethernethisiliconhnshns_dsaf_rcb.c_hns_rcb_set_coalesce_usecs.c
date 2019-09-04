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
typedef  scalar_t__ u32 ;
struct rcb_common_cb {TYPE_1__* dsaf_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (TYPE_1__*) ; 
 scalar_t__ HNS_RCB_MAX_COALESCED_USECS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ hns_rcb_get_coalesce_usecs (struct rcb_common_cb*,scalar_t__) ; 
 int /*<<< orphan*/  hns_rcb_set_port_timeout (struct rcb_common_cb*,scalar_t__,scalar_t__) ; 

int hns_rcb_set_coalesce_usecs(
	struct rcb_common_cb *rcb_common, u32 port_idx, u32 timeout)
{
	u32 old_timeout = hns_rcb_get_coalesce_usecs(rcb_common, port_idx);

	if (timeout == old_timeout)
		return 0;

	if (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) {
		if (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev)) {
			dev_err(rcb_common->dsaf_dev->dev,
				"error: not support coalesce_usecs setting!\n");
			return -EINVAL;
		}
	}
	if (timeout > HNS_RCB_MAX_COALESCED_USECS || timeout == 0) {
		dev_err(rcb_common->dsaf_dev->dev,
			"error: coalesce_usecs setting supports 1~1023us\n");
		return -EINVAL;
	}
	hns_rcb_set_port_timeout(rcb_common, port_idx, timeout);
	return 0;
}