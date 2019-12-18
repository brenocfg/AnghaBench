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
typedef  int u32 ;
struct qlcnic_adapter {TYPE_1__* ahw; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pci_func; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_XG_STATE_P3P ; 
 int EIO ; 
 int QLCRD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int*) ; 
 int XG_LINK_STATE_P3P (int /*<<< orphan*/ ,int) ; 
 int XG_LINK_UP_P3P ; 
 struct qlcnic_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int qlcnic_83xx_test_link (struct qlcnic_adapter*) ; 

__attribute__((used)) static u32 qlcnic_test_link(struct net_device *dev)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	int err = 0;
	u32 val;

	if (qlcnic_83xx_check(adapter)) {
		val = qlcnic_83xx_test_link(adapter);
		return (val & 1) ? 0 : 1;
	}
	val = QLCRD32(adapter, CRB_XG_STATE_P3P, &err);
	if (err == -EIO)
		return err;
	val = XG_LINK_STATE_P3P(adapter->ahw->pci_func, val);
	return (val == XG_LINK_UP_P3P) ? 0 : 1;
}