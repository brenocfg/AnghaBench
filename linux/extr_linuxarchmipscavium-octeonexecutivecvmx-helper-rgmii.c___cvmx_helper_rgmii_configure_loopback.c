#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int en; int duplex; int slottime; int speed; } ;
union cvmx_gmxx_prtx_cfg {int u64; TYPE_2__ s; } ;
struct TYPE_3__ {int int_loop; int ext_loop; } ;
union cvmx_asxx_prt_loop {int u64; TYPE_1__ s; } ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ASXX_PRT_LOOP (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_RX_PRT_EN (int) ; 
 int /*<<< orphan*/  CVMX_ASXX_TX_PRT_EN (int) ; 
 int /*<<< orphan*/  CVMX_GMXX_PRTX_CFG (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_BURST (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_CLK (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_TXX_SLOT (int,int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 

int __cvmx_helper_rgmii_configure_loopback(int ipd_port, int enable_internal,
					   int enable_external)
{
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);
	int original_enable;
	union cvmx_gmxx_prtx_cfg gmx_cfg;
	union cvmx_asxx_prt_loop asxx_prt_loop;

	/* Read the current enable state and save it */
	gmx_cfg.u64 = cvmx_read_csr(CVMX_GMXX_PRTX_CFG(index, interface));
	original_enable = gmx_cfg.s.en;
	/* Force port to be disabled */
	gmx_cfg.s.en = 0;
	if (enable_internal) {
		/* Force speed if we're doing internal loopback */
		gmx_cfg.s.duplex = 1;
		gmx_cfg.s.slottime = 1;
		gmx_cfg.s.speed = 1;
		cvmx_write_csr(CVMX_GMXX_TXX_CLK(index, interface), 1);
		cvmx_write_csr(CVMX_GMXX_TXX_SLOT(index, interface), 0x200);
		cvmx_write_csr(CVMX_GMXX_TXX_BURST(index, interface), 0x2000);
	}
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);

	/* Set the loopback bits */
	asxx_prt_loop.u64 = cvmx_read_csr(CVMX_ASXX_PRT_LOOP(interface));
	if (enable_internal)
		asxx_prt_loop.s.int_loop |= 1 << index;
	else
		asxx_prt_loop.s.int_loop &= ~(1 << index);
	if (enable_external)
		asxx_prt_loop.s.ext_loop |= 1 << index;
	else
		asxx_prt_loop.s.ext_loop &= ~(1 << index);
	cvmx_write_csr(CVMX_ASXX_PRT_LOOP(interface), asxx_prt_loop.u64);

	/* Force enables in internal loopback */
	if (enable_internal) {
		uint64_t tmp;
		tmp = cvmx_read_csr(CVMX_ASXX_TX_PRT_EN(interface));
		cvmx_write_csr(CVMX_ASXX_TX_PRT_EN(interface),
			       (1 << index) | tmp);
		tmp = cvmx_read_csr(CVMX_ASXX_RX_PRT_EN(interface));
		cvmx_write_csr(CVMX_ASXX_RX_PRT_EN(interface),
			       (1 << index) | tmp);
		original_enable = 1;
	}

	/* Restore the enable state */
	gmx_cfg.s.en = original_enable;
	cvmx_write_csr(CVMX_GMXX_PRTX_CFG(index, interface), gmx_cfg.u64);
	return 0;
}