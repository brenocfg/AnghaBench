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

/* Variables and functions */
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_init () ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift (int,int,int) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_shift_zeros (int,int) ; 
 int /*<<< orphan*/  cvmx_helper_qlm_jtag_update (int) ; 

void __cvmx_helper_errata_qlm_disable_2nd_order_cdr(int qlm)
{
	int lane;
	cvmx_helper_qlm_jtag_init();
	/* We need to load all four lanes of the QLM, a total of 1072 bits */
	for (lane = 0; lane < 4; lane++) {
		/*
		 * Each lane has 268 bits. We need to set
		 * cfg_cdr_incx<67:64> = 3 and cfg_cdr_secord<77> =
		 * 1. All other bits are zero. Bits go in LSB first,
		 * so start off with the zeros for bits <63:0>.
		 */
		cvmx_helper_qlm_jtag_shift_zeros(qlm, 63 - 0 + 1);
		/* cfg_cdr_incx<67:64>=3 */
		cvmx_helper_qlm_jtag_shift(qlm, 67 - 64 + 1, 3);
		/* Zeros for bits <76:68> */
		cvmx_helper_qlm_jtag_shift_zeros(qlm, 76 - 68 + 1);
		/* cfg_cdr_secord<77>=1 */
		cvmx_helper_qlm_jtag_shift(qlm, 77 - 77 + 1, 1);
		/* Zeros for bits <267:78> */
		cvmx_helper_qlm_jtag_shift_zeros(qlm, 267 - 78 + 1);
	}
	cvmx_helper_qlm_jtag_update(qlm);
}