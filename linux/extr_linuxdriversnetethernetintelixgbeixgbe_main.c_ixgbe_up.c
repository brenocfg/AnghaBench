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
struct ixgbe_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ixgbe_configure (struct ixgbe_adapter*) ; 
 int /*<<< orphan*/  ixgbe_up_complete (struct ixgbe_adapter*) ; 

void ixgbe_up(struct ixgbe_adapter *adapter)
{
	/* hardware has been reset, we need to reload some things */
	ixgbe_configure(adapter);

	ixgbe_up_complete(adapter);
}