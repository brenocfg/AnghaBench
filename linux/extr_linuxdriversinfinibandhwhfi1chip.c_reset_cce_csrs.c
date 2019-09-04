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

/* Variables and functions */
 int /*<<< orphan*/  ALL_FROZE ; 
 int /*<<< orphan*/  ALL_RXE_PAUSE ; 
 int /*<<< orphan*/  ALL_TXE_PAUSE ; 
 scalar_t__ CCE_COUNTER_ARRAY32 ; 
 int /*<<< orphan*/  CCE_CTRL_RXE_RESUME_SMASK ; 
 int /*<<< orphan*/  CCE_CTRL_SPC_UNFREEZE_SMASK ; 
 int /*<<< orphan*/  CCE_CTRL_TXE_RESUME_SMASK ; 
 scalar_t__ CCE_DC_CTRL ; 
 unsigned long long CCE_DC_CTRL_RESETCSR ; 
 scalar_t__ CCE_ERR_CLEAR ; 
 scalar_t__ CCE_ERR_MASK ; 
 scalar_t__ CCE_INT_CLEAR ; 
 scalar_t__ CCE_INT_COUNTER_ARRAY32 ; 
 scalar_t__ CCE_INT_MAP ; 
 scalar_t__ CCE_INT_MASK ; 
 scalar_t__ CCE_MSIX_INT_GRANTED ; 
 scalar_t__ CCE_MSIX_TABLE_LOWER ; 
 scalar_t__ CCE_MSIX_TABLE_UPPER ; 
 unsigned long long CCE_MSIX_TABLE_UPPER_RESETCSR ; 
 scalar_t__ CCE_MSIX_VEC_CLR_WITHOUT_INT ; 
 int CCE_NUM_32_BIT_COUNTERS ; 
 int CCE_NUM_32_BIT_INT_COUNTERS ; 
 int CCE_NUM_INT_CSRS ; 
 int CCE_NUM_INT_MAP_CSRS ; 
 int CCE_NUM_MSIX_PBAS ; 
 int CCE_NUM_MSIX_VECTORS ; 
 int CCE_NUM_SCRATCH ; 
 scalar_t__ CCE_SCRATCH ; 
 int /*<<< orphan*/  clear_cce_status (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,scalar_t__,unsigned long long) ; 

__attribute__((used)) static void reset_cce_csrs(struct hfi1_devdata *dd)
{
	int i;

	/* CCE_REVISION read-only */
	/* CCE_REVISION2 read-only */
	/* CCE_CTRL - bits clear automatically */
	/* CCE_STATUS read-only, use CceCtrl to clear */
	clear_cce_status(dd, ALL_FROZE, CCE_CTRL_SPC_UNFREEZE_SMASK);
	clear_cce_status(dd, ALL_TXE_PAUSE, CCE_CTRL_TXE_RESUME_SMASK);
	clear_cce_status(dd, ALL_RXE_PAUSE, CCE_CTRL_RXE_RESUME_SMASK);
	for (i = 0; i < CCE_NUM_SCRATCH; i++)
		write_csr(dd, CCE_SCRATCH + (8 * i), 0);
	/* CCE_ERR_STATUS read-only */
	write_csr(dd, CCE_ERR_MASK, 0);
	write_csr(dd, CCE_ERR_CLEAR, ~0ull);
	/* CCE_ERR_FORCE leave alone */
	for (i = 0; i < CCE_NUM_32_BIT_COUNTERS; i++)
		write_csr(dd, CCE_COUNTER_ARRAY32 + (8 * i), 0);
	write_csr(dd, CCE_DC_CTRL, CCE_DC_CTRL_RESETCSR);
	/* CCE_PCIE_CTRL leave alone */
	for (i = 0; i < CCE_NUM_MSIX_VECTORS; i++) {
		write_csr(dd, CCE_MSIX_TABLE_LOWER + (8 * i), 0);
		write_csr(dd, CCE_MSIX_TABLE_UPPER + (8 * i),
			  CCE_MSIX_TABLE_UPPER_RESETCSR);
	}
	for (i = 0; i < CCE_NUM_MSIX_PBAS; i++) {
		/* CCE_MSIX_PBA read-only */
		write_csr(dd, CCE_MSIX_INT_GRANTED, ~0ull);
		write_csr(dd, CCE_MSIX_VEC_CLR_WITHOUT_INT, ~0ull);
	}
	for (i = 0; i < CCE_NUM_INT_MAP_CSRS; i++)
		write_csr(dd, CCE_INT_MAP, 0);
	for (i = 0; i < CCE_NUM_INT_CSRS; i++) {
		/* CCE_INT_STATUS read-only */
		write_csr(dd, CCE_INT_MASK + (8 * i), 0);
		write_csr(dd, CCE_INT_CLEAR + (8 * i), ~0ull);
		/* CCE_INT_FORCE leave alone */
		/* CCE_INT_BLOCKED read-only */
	}
	for (i = 0; i < CCE_NUM_32_BIT_INT_COUNTERS; i++)
		write_csr(dd, CCE_INT_COUNTER_ARRAY32 + (8 * i), 0);
}