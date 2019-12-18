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
struct hns_mac_cb {scalar_t__ cpld_ctrl_reg; int /*<<< orphan*/  cpld_ctrl; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ MAC_SFP_PORT_OFFSET ; 
 int dsaf_read_syscon (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int hns_mac_get_sfp_prsnt(struct hns_mac_cb *mac_cb, int *sfp_prsnt)
{
	u32 val = 0;
	int ret;

	if (!mac_cb->cpld_ctrl)
		return -ENODEV;

	ret = dsaf_read_syscon(mac_cb->cpld_ctrl,
			       mac_cb->cpld_ctrl_reg + MAC_SFP_PORT_OFFSET,
			       &val);
	if (ret)
		return ret;

	*sfp_prsnt = !val;
	return 0;
}