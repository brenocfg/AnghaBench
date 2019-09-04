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
struct TYPE_3__ {int enable; } ;
union cvmx_pko_reg_crc_enable {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
struct TYPE_4__ {scalar_t__ board_type; } ;

/* Variables and functions */
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  CVMX_PKO_REG_CRC_ENABLE ; 
 int /*<<< orphan*/  __cvmx_helper_setup_gmx (int,int) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_spi4000_is_present (int) ; 
 TYPE_2__* cvmx_sysinfo_get () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __cvmx_helper_spi_probe(int interface)
{
	int num_ports = 0;

	if ((cvmx_sysinfo_get()->board_type != CVMX_BOARD_TYPE_SIM) &&
	    cvmx_spi4000_is_present(interface)) {
		num_ports = 10;
	} else {
		union cvmx_pko_reg_crc_enable enable;
		num_ports = 16;
		/*
		 * Unlike the SPI4000, most SPI devices don't
		 * automatically put on the L2 CRC. For everything
		 * except for the SPI4000 have PKO append the L2 CRC
		 * to the packet.
		 */
		enable.u64 = cvmx_read_csr(CVMX_PKO_REG_CRC_ENABLE);
		enable.s.enable |= 0xffff << (interface * 16);
		cvmx_write_csr(CVMX_PKO_REG_CRC_ENABLE, enable.u64);
	}
	__cvmx_helper_setup_gmx(interface, num_ports);
	return num_ports;
}