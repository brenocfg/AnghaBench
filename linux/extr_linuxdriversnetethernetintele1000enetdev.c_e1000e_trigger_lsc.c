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
struct e1000_hw {int dummy; } ;
struct e1000_adapter {scalar_t__ msix_entries; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_ICS_LSC ; 
 int E1000_ICS_OTHER ; 
 int /*<<< orphan*/  ICS ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void e1000e_trigger_lsc(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;

	if (adapter->msix_entries)
		ew32(ICS, E1000_ICS_LSC | E1000_ICS_OTHER);
	else
		ew32(ICS, E1000_ICS_LSC);
}