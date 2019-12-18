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
struct qlcnic_adapter {TYPE_1__* dcb; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 scalar_t__ qlcnic_82xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_82xx_dcb_ops ; 
 scalar_t__ qlcnic_83xx_check (struct qlcnic_adapter*) ; 
 int /*<<< orphan*/  qlcnic_83xx_dcb_ops ; 

__attribute__((used)) static void qlcnic_set_dcb_ops(struct qlcnic_adapter *adapter)
{
	if (qlcnic_82xx_check(adapter))
		adapter->dcb->ops = &qlcnic_82xx_dcb_ops;
	else if (qlcnic_83xx_check(adapter))
		adapter->dcb->ops = &qlcnic_83xx_dcb_ops;
}