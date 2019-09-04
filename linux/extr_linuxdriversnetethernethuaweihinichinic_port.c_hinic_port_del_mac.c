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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct hinic_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_DEL ; 
 int change_mac (struct hinic_dev*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hinic_port_del_mac(struct hinic_dev *nic_dev, const u8 *addr,
		       u16 vlan_id)
{
	return change_mac(nic_dev, addr, vlan_id, MAC_DEL);
}