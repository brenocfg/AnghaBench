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
struct e1000_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  e1000_free_desc_rings (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_loopback_cleanup (struct e1000_adapter*) ; 
 int e1000_run_loopback_test (struct e1000_adapter*) ; 
 int e1000_setup_desc_rings (struct e1000_adapter*) ; 
 int e1000_setup_loopback_test (struct e1000_adapter*) ; 

__attribute__((used)) static int e1000_loopback_test(struct e1000_adapter *adapter, u64 *data)
{
	*data = e1000_setup_desc_rings(adapter);
	if (*data)
		goto out;
	*data = e1000_setup_loopback_test(adapter);
	if (*data)
		goto err_loopback;
	*data = e1000_run_loopback_test(adapter);
	e1000_loopback_cleanup(adapter);

err_loopback:
	e1000_free_desc_rings(adapter);
out:
	return *data;
}