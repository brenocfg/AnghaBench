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
 int /*<<< orphan*/  __ICE_RESET_RECOVERY_PENDING ; 
 int test_bit (int /*<<< orphan*/ ,unsigned long*) ; 

__attribute__((used)) static bool ice_is_reset_recovery_pending(unsigned long int *state)
{
	return test_bit(__ICE_RESET_RECOVERY_PENDING, state);
}