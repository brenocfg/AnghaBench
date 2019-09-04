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
typedef  int /*<<< orphan*/  u32 ;
struct ixgb_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL0 ; 
 int /*<<< orphan*/  IXGB_CTRL0_VME ; 
 int /*<<< orphan*/  IXGB_READ_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgb_vlan_strip_enable(struct ixgb_adapter *adapter)
{
	u32 ctrl;

	/* enable VLAN tag insert/strip */
	ctrl = IXGB_READ_REG(&adapter->hw, CTRL0);
	ctrl |= IXGB_CTRL0_VME;
	IXGB_WRITE_REG(&adapter->hw, CTRL0, ctrl);
}