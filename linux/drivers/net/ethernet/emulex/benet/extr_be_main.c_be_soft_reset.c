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
typedef  int /*<<< orphan*/  u32 ;
struct be_adapter {scalar_t__ pcicfg; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SLIPORT_SOFTRESET_OFFSET ; 
 int /*<<< orphan*/  SLIPORT_SOFTRESET_SR_MASK ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void be_soft_reset(struct be_adapter *adapter)
{
	u32 val;

	dev_info(&adapter->pdev->dev, "Initiating chip soft reset\n");
	val = ioread32(adapter->pcicfg + SLIPORT_SOFTRESET_OFFSET);
	val |= SLIPORT_SOFTRESET_SR_MASK;
	iowrite32(val, adapter->pcicfg + SLIPORT_SOFTRESET_OFFSET);
}