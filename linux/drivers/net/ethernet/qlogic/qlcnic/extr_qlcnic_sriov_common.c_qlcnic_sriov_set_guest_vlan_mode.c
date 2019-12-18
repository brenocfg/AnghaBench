#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct qlcnic_sriov {int any_vlan; int num_allowed_vlans; int /*<<< orphan*/ * allowed_vlans; } ;
struct TYPE_6__ {int* arg; } ;
struct qlcnic_cmd_args {TYPE_3__ rsp; } ;
struct qlcnic_adapter {TYPE_2__* pdev; TYPE_1__* ahw; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {struct qlcnic_sriov* sriov; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlcnic_sriov_alloc_vlans (struct qlcnic_adapter*) ; 

__attribute__((used)) static int qlcnic_sriov_set_guest_vlan_mode(struct qlcnic_adapter *adapter,
					    struct qlcnic_cmd_args *cmd)
{
	struct qlcnic_sriov *sriov = adapter->ahw->sriov;
	int i, num_vlans;
	u16 *vlans;

	if (sriov->allowed_vlans)
		return 0;

	sriov->any_vlan = cmd->rsp.arg[2] & 0xf;
	sriov->num_allowed_vlans = cmd->rsp.arg[2] >> 16;
	dev_info(&adapter->pdev->dev, "Number of allowed Guest VLANs = %d\n",
		 sriov->num_allowed_vlans);

	qlcnic_sriov_alloc_vlans(adapter);

	if (!sriov->any_vlan)
		return 0;

	num_vlans = sriov->num_allowed_vlans;
	sriov->allowed_vlans = kcalloc(num_vlans, sizeof(u16), GFP_KERNEL);
	if (!sriov->allowed_vlans)
		return -ENOMEM;

	vlans = (u16 *)&cmd->rsp.arg[3];
	for (i = 0; i < num_vlans; i++)
		sriov->allowed_vlans[i] = vlans[i];

	return 0;
}