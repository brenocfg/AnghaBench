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

/* Variables and functions */
 int /*<<< orphan*/  ac_wake_req_state ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

bool db8500_prcmu_is_ac_wake_requested(void)
{
	return (atomic_read(&ac_wake_req_state) != 0);
}