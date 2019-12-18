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
struct intr_info {int member_0; char* member_1; int member_2; int member_3; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_MPS_INT_CAUSE ; 
 int /*<<< orphan*/  t3_fatal_err (struct adapter*) ; 
 scalar_t__ t3_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,int,struct intr_info const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mps_intr_handler(struct adapter *adapter)
{
	static const struct intr_info mps_intr_info[] = {
		{0x1ff, "MPS parity error", -1, 1},
		{0}
	};

	if (t3_handle_intr_status(adapter, A_MPS_INT_CAUSE, 0xffffffff,
				  mps_intr_info, NULL))
		t3_fatal_err(adapter);
}