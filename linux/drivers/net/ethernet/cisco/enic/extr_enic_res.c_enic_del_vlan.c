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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct enic {int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_VLAN_DEL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  enic_get_dev (struct enic*) ; 
 int vnic_dev_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int enic_del_vlan(struct enic *enic, u16 vlanid)
{
	u64 a0 = vlanid, a1 = 0;
	int wait = 1000;
	int err;

	err = vnic_dev_cmd(enic->vdev, CMD_VLAN_DEL, &a0, &a1, wait);
	if (err)
		dev_err(enic_get_dev(enic), "Can't delete vlan id, %d\n", err);

	return err;
}