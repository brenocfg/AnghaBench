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
struct hfi1_pportdata {int dummy; } ;
struct hfi1_devdata {scalar_t__ hfi1_id; struct hfi1_pportdata* pport; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_QSFP1_CLEAR ; 
 int /*<<< orphan*/  ASIC_QSFP1_INVERT ; 
 int /*<<< orphan*/  ASIC_QSFP1_MASK ; 
 int /*<<< orphan*/  ASIC_QSFP2_CLEAR ; 
 int /*<<< orphan*/  ASIC_QSFP2_INVERT ; 
 int /*<<< orphan*/  ASIC_QSFP2_MASK ; 
 int /*<<< orphan*/  QSFP1_INT ; 
 int /*<<< orphan*/  QSFP2_INT ; 
 int QSFP_HFI0_INT_N ; 
 int QSFP_HFI0_MODPRST_N ; 
 scalar_t__ qsfp_mod_present (struct hfi1_pportdata*) ; 
 int /*<<< orphan*/  set_intr_bits (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_qsfp_int_n (struct hfi1_pportdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_qsfp_int(struct hfi1_devdata *dd)
{
	struct hfi1_pportdata *ppd = dd->pport;
	u64 qsfp_mask;

	qsfp_mask = (u64)(QSFP_HFI0_INT_N | QSFP_HFI0_MODPRST_N);
	/* Clear current status to avoid spurious interrupts */
	write_csr(dd, dd->hfi1_id ? ASIC_QSFP2_CLEAR : ASIC_QSFP1_CLEAR,
		  qsfp_mask);
	write_csr(dd, dd->hfi1_id ? ASIC_QSFP2_MASK : ASIC_QSFP1_MASK,
		  qsfp_mask);

	set_qsfp_int_n(ppd, 0);

	/* Handle active low nature of INT_N and MODPRST_N pins */
	if (qsfp_mod_present(ppd))
		qsfp_mask &= ~(u64)QSFP_HFI0_MODPRST_N;
	write_csr(dd,
		  dd->hfi1_id ? ASIC_QSFP2_INVERT : ASIC_QSFP1_INVERT,
		  qsfp_mask);

	/* Enable the appropriate QSFP IRQ source */
	if (!dd->hfi1_id)
		set_intr_bits(dd, QSFP1_INT, QSFP1_INT, true);
	else
		set_intr_bits(dd, QSFP2_INT, QSFP2_INT, true);
}