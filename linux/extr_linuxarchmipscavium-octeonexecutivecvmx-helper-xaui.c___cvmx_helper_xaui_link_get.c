#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int rcv_lnk; } ;
union cvmx_pcsxx_status1_reg {TYPE_3__ s; void* u64; } ;
struct TYPE_7__ {scalar_t__ ls; } ;
union cvmx_gmxx_tx_xaui_ctl {TYPE_1__ s; void* u64; } ;
struct TYPE_8__ {scalar_t__ status; } ;
union cvmx_gmxx_rx_xaui_ctl {TYPE_2__ s; void* u64; } ;
struct TYPE_10__ {int link_up; int full_duplex; int speed; } ;
struct TYPE_11__ {TYPE_4__ s; scalar_t__ u64; } ;
typedef  TYPE_5__ cvmx_helper_link_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_EN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RX_XAUI_CTL (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TX_INT_EN (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TX_XAUI_CTL (int) ; 
 int /*<<< orphan*/  CVMX_PCSXX_INT_EN_REG (int) ; 
 int /*<<< orphan*/  CVMX_PCSXX_STATUS1_REG (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

cvmx_helper_link_info_t __cvmx_helper_xaui_link_get(int ipd_port)
{
	int interface = cvmx_helper_get_interface_num(ipd_port);
	union cvmx_gmxx_tx_xaui_ctl gmxx_tx_xaui_ctl;
	union cvmx_gmxx_rx_xaui_ctl gmxx_rx_xaui_ctl;
	union cvmx_pcsxx_status1_reg pcsxx_status1_reg;
	cvmx_helper_link_info_t result;

	gmxx_tx_xaui_ctl.u64 = cvmx_read_csr(CVMX_GMXX_TX_XAUI_CTL(interface));
	gmxx_rx_xaui_ctl.u64 = cvmx_read_csr(CVMX_GMXX_RX_XAUI_CTL(interface));
	pcsxx_status1_reg.u64 =
	    cvmx_read_csr(CVMX_PCSXX_STATUS1_REG(interface));
	result.u64 = 0;

	/* Only return a link if both RX and TX are happy */
	if ((gmxx_tx_xaui_ctl.s.ls == 0) && (gmxx_rx_xaui_ctl.s.status == 0) &&
	    (pcsxx_status1_reg.s.rcv_lnk == 1)) {
		result.s.link_up = 1;
		result.s.full_duplex = 1;
		result.s.speed = 10000;
	} else {
		/* Disable GMX and PCSX interrupts. */
		cvmx_write_csr(CVMX_GMXX_RXX_INT_EN(0, interface), 0x0);
		cvmx_write_csr(CVMX_GMXX_TX_INT_EN(interface), 0x0);
		cvmx_write_csr(CVMX_PCSXX_INT_EN_REG(interface), 0x0);
	}
	return result;
}