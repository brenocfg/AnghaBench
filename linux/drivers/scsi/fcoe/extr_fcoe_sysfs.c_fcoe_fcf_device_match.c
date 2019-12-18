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
struct fcoe_fcf_device {scalar_t__ switch_name; scalar_t__ fabric_name; scalar_t__ fc_map; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fcoe_fcf_device_match(struct fcoe_fcf_device *new,
				 struct fcoe_fcf_device *old)
{
	if (new->switch_name == old->switch_name &&
	    new->fabric_name == old->fabric_name &&
	    new->fc_map == old->fc_map &&
	    ether_addr_equal(new->mac, old->mac))
		return 1;
	return 0;
}