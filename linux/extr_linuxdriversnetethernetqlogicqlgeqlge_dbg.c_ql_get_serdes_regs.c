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
typedef  int u32 ;
struct ql_mpi_coredump {int* serdes2_xaui_an; int* serdes_xaui_an; int* serdes2_xaui_hss_pcs; int* serdes_xaui_hss_pcs; int* serdes2_xfi_an; int* serdes_xfi_an; int* serdes2_xfi_train; int* serdes_xfi_train; int* serdes2_xfi_hss_pcs; int* serdes_xfi_hss_pcs; int* serdes2_xfi_hss_tx; int* serdes_xfi_hss_tx; int* serdes2_xfi_hss_rx; int* serdes_xfi_hss_rx; int* serdes2_xfi_hss_pll; int* serdes_xfi_hss_pll; } ;
struct ql_adapter {int func; } ;

/* Variables and functions */
 int /*<<< orphan*/  XG_SERDES_ADDR_STS ; 
 int XG_SERDES_ADDR_XAUI_PWR_DOWN ; 
 int XG_SERDES_ADDR_XFI1_PWR_UP ; 
 int XG_SERDES_ADDR_XFI2_PWR_UP ; 
 int /*<<< orphan*/  XG_SERDES_XAUI_HSS_PCS_START ; 
 int /*<<< orphan*/  ql_get_both_serdes (struct ql_adapter*,unsigned int,int*,int*,unsigned int,unsigned int) ; 
 int ql_read_other_func_serdes_reg (struct ql_adapter*,int /*<<< orphan*/ ,int*) ; 
 int ql_read_serdes_reg (struct ql_adapter*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ql_get_serdes_regs(struct ql_adapter *qdev,
				struct ql_mpi_coredump *mpi_coredump)
{
	int status;
	unsigned int xfi_direct_valid, xfi_indirect_valid, xaui_direct_valid;
	unsigned int xaui_indirect_valid, i;
	u32 *direct_ptr, temp;
	u32 *indirect_ptr;

	xfi_direct_valid = xfi_indirect_valid = 0;
	xaui_direct_valid = xaui_indirect_valid = 1;

	/* The XAUI needs to be read out per port */
	status = ql_read_other_func_serdes_reg(qdev,
			XG_SERDES_XAUI_HSS_PCS_START, &temp);
	if (status)
		temp = XG_SERDES_ADDR_XAUI_PWR_DOWN;

	if ((temp & XG_SERDES_ADDR_XAUI_PWR_DOWN) ==
				XG_SERDES_ADDR_XAUI_PWR_DOWN)
		xaui_indirect_valid = 0;

	status = ql_read_serdes_reg(qdev, XG_SERDES_XAUI_HSS_PCS_START, &temp);

	if (status)
		temp = XG_SERDES_ADDR_XAUI_PWR_DOWN;

	if ((temp & XG_SERDES_ADDR_XAUI_PWR_DOWN) ==
				XG_SERDES_ADDR_XAUI_PWR_DOWN)
		xaui_direct_valid = 0;

	/*
	 * XFI register is shared so only need to read one
	 * functions and then check the bits.
	 */
	status = ql_read_serdes_reg(qdev, XG_SERDES_ADDR_STS, &temp);
	if (status)
		temp = 0;

	if ((temp & XG_SERDES_ADDR_XFI1_PWR_UP) ==
					XG_SERDES_ADDR_XFI1_PWR_UP) {
		/* now see if i'm NIC 1 or NIC 2 */
		if (qdev->func & 1)
			/* I'm NIC 2, so the indirect (NIC1) xfi is up. */
			xfi_indirect_valid = 1;
		else
			xfi_direct_valid = 1;
	}
	if ((temp & XG_SERDES_ADDR_XFI2_PWR_UP) ==
					XG_SERDES_ADDR_XFI2_PWR_UP) {
		/* now see if i'm NIC 1 or NIC 2 */
		if (qdev->func & 1)
			/* I'm NIC 2, so the indirect (NIC1) xfi is up. */
			xfi_direct_valid = 1;
		else
			xfi_indirect_valid = 1;
	}

	/* Get XAUI_AN register block. */
	if (qdev->func & 1) {
		/* Function 2 is direct	*/
		direct_ptr = mpi_coredump->serdes2_xaui_an;
		indirect_ptr = mpi_coredump->serdes_xaui_an;
	} else {
		/* Function 1 is direct	*/
		direct_ptr = mpi_coredump->serdes_xaui_an;
		indirect_ptr = mpi_coredump->serdes2_xaui_an;
	}

	for (i = 0; i <= 0x000000034; i += 4, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xaui_direct_valid, xaui_indirect_valid);

	/* Get XAUI_HSS_PCS register block. */
	if (qdev->func & 1) {
		direct_ptr =
			mpi_coredump->serdes2_xaui_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes_xaui_hss_pcs;
	} else {
		direct_ptr =
			mpi_coredump->serdes_xaui_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes2_xaui_hss_pcs;
	}

	for (i = 0x800; i <= 0x880; i += 4, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xaui_direct_valid, xaui_indirect_valid);

	/* Get XAUI_XFI_AN register block. */
	if (qdev->func & 1) {
		direct_ptr = mpi_coredump->serdes2_xfi_an;
		indirect_ptr = mpi_coredump->serdes_xfi_an;
	} else {
		direct_ptr = mpi_coredump->serdes_xfi_an;
		indirect_ptr = mpi_coredump->serdes2_xfi_an;
	}

	for (i = 0x1000; i <= 0x1034; i += 4, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_TRAIN register block. */
	if (qdev->func & 1) {
		direct_ptr = mpi_coredump->serdes2_xfi_train;
		indirect_ptr =
			mpi_coredump->serdes_xfi_train;
	} else {
		direct_ptr = mpi_coredump->serdes_xfi_train;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_train;
	}

	for (i = 0x1050; i <= 0x107c; i += 4, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_PCS register block. */
	if (qdev->func & 1) {
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_pcs;
	} else {
		direct_ptr =
			mpi_coredump->serdes_xfi_hss_pcs;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_pcs;
	}

	for (i = 0x1800; i <= 0x1838; i += 4, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_TX register block. */
	if (qdev->func & 1) {
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_tx;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_tx;
	} else {
		direct_ptr = mpi_coredump->serdes_xfi_hss_tx;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_tx;
	}
	for (i = 0x1c00; i <= 0x1c1f; i++, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);

	/* Get XAUI_XFI_HSS_RX register block. */
	if (qdev->func & 1) {
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_rx;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_rx;
	} else {
		direct_ptr = mpi_coredump->serdes_xfi_hss_rx;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_rx;
	}

	for (i = 0x1c40; i <= 0x1c5f; i++, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);


	/* Get XAUI_XFI_HSS_PLL register block. */
	if (qdev->func & 1) {
		direct_ptr =
			mpi_coredump->serdes2_xfi_hss_pll;
		indirect_ptr =
			mpi_coredump->serdes_xfi_hss_pll;
	} else {
		direct_ptr =
			mpi_coredump->serdes_xfi_hss_pll;
		indirect_ptr =
			mpi_coredump->serdes2_xfi_hss_pll;
	}
	for (i = 0x1e00; i <= 0x1e1f; i++, direct_ptr++, indirect_ptr++)
		ql_get_both_serdes(qdev, i, direct_ptr, indirect_ptr,
					xfi_direct_valid, xfi_indirect_valid);
	return 0;
}