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
struct hfi1_devdata {int dc_shutdown; int /*<<< orphan*/  dc8051_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_DC8051_CFG_RST ; 
 int /*<<< orphan*/  lcb_shutdown (struct hfi1_devdata*,int) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _dc_shutdown(struct hfi1_devdata *dd)
{
	lockdep_assert_held(&dd->dc8051_lock);

	if (dd->dc_shutdown)
		return;

	dd->dc_shutdown = 1;
	/* Shutdown the LCB */
	lcb_shutdown(dd, 1);
	/*
	 * Going to OFFLINE would have causes the 8051 to put the
	 * SerDes into reset already. Just need to shut down the 8051,
	 * itself.
	 */
	write_csr(dd, DC_DC8051_CFG_RST, 0x1);
}