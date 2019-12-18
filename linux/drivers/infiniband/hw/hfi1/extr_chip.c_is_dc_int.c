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
struct hfi1_devdata {int dummy; } ;
struct err_reg_info {scalar_t__ handler; } ;

/* Variables and functions */
 struct err_reg_info* dc_errs ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,...) ; 
 int /*<<< orphan*/  interrupt_clear_down (struct hfi1_devdata*,int /*<<< orphan*/ ,struct err_reg_info const*) ; 

__attribute__((used)) static void is_dc_int(struct hfi1_devdata *dd, unsigned int source)
{
	const struct err_reg_info *eri = &dc_errs[source];

	if (eri->handler) {
		interrupt_clear_down(dd, 0, eri);
	} else if (source == 3 /* dc_lbm_int */) {
		/*
		 * This indicates that a parity error has occurred on the
		 * address/control lines presented to the LBM.  The error
		 * is a single pulse, there is no associated error flag,
		 * and it is non-maskable.  This is because if a parity
		 * error occurs on the request the request is dropped.
		 * This should never occur, but it is nice to know if it
		 * ever does.
		 */
		dd_dev_err(dd, "Parity error in DC LBM block\n");
	} else {
		dd_dev_err(dd, "Invalid DC interrupt %u\n", source);
	}
}