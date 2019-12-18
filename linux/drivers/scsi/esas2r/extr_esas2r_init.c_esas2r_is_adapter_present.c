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
struct esas2r_adapter {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_NOT_PRESENT ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

bool esas2r_is_adapter_present(struct esas2r_adapter *a)
{
	if (test_bit(AF_NOT_PRESENT, &a->flags))
		return false;

	if (esas2r_read_register_dword(a, MU_DOORBELL_OUT) == 0xFFFFFFFF) {
		set_bit(AF_NOT_PRESENT, &a->flags);

		return false;
	}
	return true;
}