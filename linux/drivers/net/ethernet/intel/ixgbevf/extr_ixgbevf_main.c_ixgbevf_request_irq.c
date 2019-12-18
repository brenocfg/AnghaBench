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
struct ixgbevf_adapter {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  hw_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int ixgbevf_request_msix_irqs (struct ixgbevf_adapter*) ; 

__attribute__((used)) static int ixgbevf_request_irq(struct ixgbevf_adapter *adapter)
{
	int err = ixgbevf_request_msix_irqs(adapter);

	if (err)
		hw_dbg(&adapter->hw, "request_irq failed, Error %d\n", err);

	return err;
}