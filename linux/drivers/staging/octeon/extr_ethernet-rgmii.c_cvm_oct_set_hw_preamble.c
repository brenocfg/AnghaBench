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
struct TYPE_4__ {unsigned long long port_bit; } ;
union cvmx_ipd_sub_port_fcs {void* u64; TYPE_2__ s; } ;
union cvmx_gmxx_rxx_int_reg {void* u64; } ;
struct TYPE_3__ {int pre_chk; } ;
union cvmx_gmxx_rxx_frm_ctl {void* u64; TYPE_1__ s; } ;
struct octeon_ethernet {unsigned long long port; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_RXX_FRM_CTL (int,int) ; 
 int /*<<< orphan*/  CVMX_GMXX_RXX_INT_REG (int,int) ; 
 int /*<<< orphan*/  CVMX_IPD_SUB_PORT_FCS ; 
 int INDEX (unsigned long long) ; 
 int INTERFACE (unsigned long long) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void cvm_oct_set_hw_preamble(struct octeon_ethernet *priv, bool enable)
{
	union cvmx_gmxx_rxx_frm_ctl gmxx_rxx_frm_ctl;
	union cvmx_ipd_sub_port_fcs ipd_sub_port_fcs;
	union cvmx_gmxx_rxx_int_reg gmxx_rxx_int_reg;
	int interface = INTERFACE(priv->port);
	int index = INDEX(priv->port);

	/* Set preamble checking. */
	gmxx_rxx_frm_ctl.u64 = cvmx_read_csr(CVMX_GMXX_RXX_FRM_CTL(index,
								   interface));
	gmxx_rxx_frm_ctl.s.pre_chk = enable;
	cvmx_write_csr(CVMX_GMXX_RXX_FRM_CTL(index, interface),
		       gmxx_rxx_frm_ctl.u64);

	/* Set FCS stripping. */
	ipd_sub_port_fcs.u64 = cvmx_read_csr(CVMX_IPD_SUB_PORT_FCS);
	if (enable)
		ipd_sub_port_fcs.s.port_bit |= 1ull << priv->port;
	else
		ipd_sub_port_fcs.s.port_bit &=
					0xffffffffull ^ (1ull << priv->port);
	cvmx_write_csr(CVMX_IPD_SUB_PORT_FCS, ipd_sub_port_fcs.u64);

	/* Clear any error bits. */
	gmxx_rxx_int_reg.u64 = cvmx_read_csr(CVMX_GMXX_RXX_INT_REG(index,
								   interface));
	cvmx_write_csr(CVMX_GMXX_RXX_INT_REG(index, interface),
		       gmxx_rxx_int_reg.u64);
}