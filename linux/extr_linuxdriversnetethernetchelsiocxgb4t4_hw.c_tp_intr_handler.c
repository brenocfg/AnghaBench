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
#define  FLMTXFLSTEMPTY_F 128 
 int /*<<< orphan*/  TP_INT_CAUSE_A ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 scalar_t__ t4_handle_intr_status (struct adapter*,int /*<<< orphan*/ ,struct intr_info const*) ; 

__attribute__((used)) static void tp_intr_handler(struct adapter *adapter)
{
	static const struct intr_info tp_intr_info[] = {
		{ 0x3fffffff, "TP parity error", -1, 1 },
		{ FLMTXFLSTEMPTY_F, "TP out of Tx pages", -1, 1 },
		{ 0 }
	};

	if (t4_handle_intr_status(adapter, TP_INT_CAUSE_A, tp_intr_info))
		t4_fatal_err(adapter);
}