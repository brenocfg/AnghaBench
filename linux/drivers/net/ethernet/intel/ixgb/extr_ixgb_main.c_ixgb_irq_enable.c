#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {scalar_t__ subsystem_vendor_id; } ;
struct ixgb_adapter {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMS ; 
 int IXGB_INT_GPI0 ; 
 int IXGB_INT_LSC ; 
 int IXGB_INT_RXDMT0 ; 
 int IXGB_INT_RXT0 ; 
 int IXGB_INT_TXDW ; 
 int /*<<< orphan*/  IXGB_WRITE_FLUSH (TYPE_1__*) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI_VENDOR_ID_SUN ; 

__attribute__((used)) static void
ixgb_irq_enable(struct ixgb_adapter *adapter)
{
	u32 val = IXGB_INT_RXT0 | IXGB_INT_RXDMT0 |
		  IXGB_INT_TXDW | IXGB_INT_LSC;
	if (adapter->hw.subsystem_vendor_id == PCI_VENDOR_ID_SUN)
		val |= IXGB_INT_GPI0;
	IXGB_WRITE_REG(&adapter->hw, IMS, val);
	IXGB_WRITE_FLUSH(&adapter->hw);
}