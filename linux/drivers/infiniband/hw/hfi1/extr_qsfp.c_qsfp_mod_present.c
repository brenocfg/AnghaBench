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
typedef  int u64 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {scalar_t__ hfi1_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASIC_QSFP1_IN ; 
 int /*<<< orphan*/  ASIC_QSFP2_IN ; 
 int QSFP_HFI0_MODPRST_N ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

int qsfp_mod_present(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 reg;

	reg = read_csr(dd, dd->hfi1_id ? ASIC_QSFP2_IN : ASIC_QSFP1_IN);
	return !(reg & QSFP_HFI0_MODPRST_N);
}