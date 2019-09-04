#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ board_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_RX_CLK_SETX (int,int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_CLK_SETX (int,int) ; 
 scalar_t__ CVMX_BOARD_TYPE_CN3005_EVB_HS5 ; 
 scalar_t__ CVMX_BOARD_TYPE_UBNT_E100 ; 
 TYPE_1__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int __cvmx_helper_board_hardware_enable(int interface)
{
	if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_CN3005_EVB_HS5) {
		if (interface == 0) {
			/* Different config for switch port */
			cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(1, interface), 0);
			cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(1, interface), 0);
			/*
			 * Boards with gigabit WAN ports need a
			 * different setting that is compatible with
			 * 100 Mbit settings
			 */
			cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(0, interface),
				       0xc);
			cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(0, interface),
				       0xc);
		}
	} else if (cvmx_sysinfo_get()->board_type ==
			CVMX_BOARD_TYPE_UBNT_E100) {
		cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(0, interface), 0);
		cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(0, interface), 0x10);
		cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(1, interface), 0);
		cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(1, interface), 0x10);
		cvmx_write_csr(CVMX_ASXX_RX_CLK_SETX(2, interface), 0);
		cvmx_write_csr(CVMX_ASXX_TX_CLK_SETX(2, interface), 0x10);
	}
	return 0;
}