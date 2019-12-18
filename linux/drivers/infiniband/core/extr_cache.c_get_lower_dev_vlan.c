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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 int /*<<< orphan*/  vlan_dev_vlan_id (struct net_device*) ; 

__attribute__((used)) static int get_lower_dev_vlan(struct net_device *lower_dev, void *data)
{
	u16 *vlan_id = data;

	if (is_vlan_dev(lower_dev))
		*vlan_id = vlan_dev_vlan_id(lower_dev);

	/* We are interested only in first level vlan device, so
	 * always return 1 to stop iterating over next level devices.
	 */
	return 1;
}