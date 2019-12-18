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
typedef  int /*<<< orphan*/  u64 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {scalar_t__ hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_QSFP1_OUT ; 
 int /*<<< orphan*/  ASIC_QSFP2_OUT ; 
 scalar_t__ QSFP_HFI0_RESET_N ; 
 int /*<<< orphan*/  read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_qsfp_int_n (struct hfi1_pportdata*,int) ; 
 int set_qsfp_tx (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  wait_for_qsfp_init (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int reset_qsfp(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 mask, qsfp_mask;

	/* Disable INT_N from triggering QSFP interrupts */
	set_qsfp_int_n(ppd, 0);

	/* Reset the QSFP */
	mask = (u64)QSFP_HFI0_RESET_N;

	qsfp_mask = read_csr(dd,
			     dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT);
	qsfp_mask &= ~mask;
	write_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT, qsfp_mask);

	udelay(10);

	qsfp_mask |= mask;
	write_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_OUT : ASIC_QSFP1_OUT, qsfp_mask);

	wait_for_qsfp_init(ppd);

	/*
	 * Allow INT_N to trigger the QSFP interrupt to watch
	 * for alarms and warnings
	 */
	set_qsfp_int_n(ppd, 1);

	/*
	 * After the reset, AOC transmitters are enabled by default. They need
	 * to be turned off to complete the QSFP setup before they can be
	 * enabled again.
	 */
	return set_qsfp_tx(ppd, 0);
}