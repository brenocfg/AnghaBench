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
struct ixgbevf_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbevf_configure (struct ixgbevf_adapter*) ; 
 int /*<<< orphan*/  ixgbevf_up_complete (struct ixgbevf_adapter*) ; 

void ixgbevf_up(struct ixgbevf_adapter *adapter)
{
	ixgbevf_configure(adapter);

	ixgbevf_up_complete(adapter);
}