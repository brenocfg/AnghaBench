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
typedef  int u64 ;
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_free_desc_rings (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_loopback_cleanup (struct ixgbe_adapter*) ; 
 int ixgbe_run_loopback_test (struct ixgbe_adapter*) ; 
 int ixgbe_setup_desc_rings (struct ixgbe_adapter*) ; 
 int ixgbe_setup_loopback_test (struct ixgbe_adapter*) ; 

__attribute__((used)) static int ixgbe_loopback_test(struct ixgbe_adapter *adapter, u64 *data)
{
	*data = ixgbe_setup_desc_rings(adapter);
	if (*data)
		goto out;
	*data = ixgbe_setup_loopback_test(adapter);
	if (*data)
		goto err_loopback;
	*data = ixgbe_run_loopback_test(adapter);
	ixgbe_loopback_cleanup(adapter);

err_loopback:
	ixgbe_free_desc_rings(adapter);
out:
	return *data;
}