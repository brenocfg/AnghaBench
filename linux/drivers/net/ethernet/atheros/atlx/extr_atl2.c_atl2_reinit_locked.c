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
struct atl2_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ATL2_RESETTING ; 
 int /*<<< orphan*/  atl2_down (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_up (struct atl2_adapter*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl2_reinit_locked(struct atl2_adapter *adapter)
{
	WARN_ON(in_interrupt());
	while (test_and_set_bit(__ATL2_RESETTING, &adapter->flags))
		msleep(1);
	atl2_down(adapter);
	atl2_up(adapter);
	clear_bit(__ATL2_RESETTING, &adapter->flags);
}