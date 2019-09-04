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
struct TYPE_4__ {int loopbck1; } ;
union cvmx_pcsx_mrx_control_reg {void* u64; TYPE_2__ s; } ;
struct TYPE_3__ {int loopbck2; } ;
union cvmx_pcsx_miscx_ctl_reg {void* u64; TYPE_1__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_PCSX_MISCX_CTL_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_PCSX_MRX_CONTROL_REG (int,int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_hardware_init_link (int,int) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

int __cvmx_helper_sgmii_configure_loopback(int ipd_port, int enable_internal,
					   int enable_external)
{
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);
	union cvmx_pcsx_mrx_control_reg pcsx_mrx_control_reg;
	union cvmx_pcsx_miscx_ctl_reg pcsx_miscx_ctl_reg;

	pcsx_mrx_control_reg.u64 =
	    cvmx_read_csr(CVMX_PCSX_MRX_CONTROL_REG(index, interface));
	pcsx_mrx_control_reg.s.loopbck1 = enable_internal;
	cvmx_write_csr(CVMX_PCSX_MRX_CONTROL_REG(index, interface),
		       pcsx_mrx_control_reg.u64);

	pcsx_miscx_ctl_reg.u64 =
	    cvmx_read_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface));
	pcsx_miscx_ctl_reg.s.loopbck2 = enable_external;
	cvmx_write_csr(CVMX_PCSX_MISCX_CTL_REG(index, interface),
		       pcsx_miscx_ctl_reg.u64);

	__cvmx_helper_sgmii_hardware_init_link(interface, index);
	return 0;
}