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
typedef  int /*<<< orphan*/  cvmx_helper_link_info_t ;

/* Variables and functions */
#define  CVMX_HELPER_INTERFACE_MODE_DISABLED 137 
#define  CVMX_HELPER_INTERFACE_MODE_GMII 136 
#define  CVMX_HELPER_INTERFACE_MODE_LOOP 135 
#define  CVMX_HELPER_INTERFACE_MODE_NPI 134 
#define  CVMX_HELPER_INTERFACE_MODE_PCIE 133 
#define  CVMX_HELPER_INTERFACE_MODE_PICMG 132 
#define  CVMX_HELPER_INTERFACE_MODE_RGMII 131 
#define  CVMX_HELPER_INTERFACE_MODE_SGMII 130 
#define  CVMX_HELPER_INTERFACE_MODE_SPI 129 
#define  CVMX_HELPER_INTERFACE_MODE_XAUI 128 
 int __cvmx_helper_rgmii_link_set (int,int /*<<< orphan*/ ) ; 
 int __cvmx_helper_sgmii_link_set (int,int /*<<< orphan*/ ) ; 
 int __cvmx_helper_spi_link_set (int,int /*<<< orphan*/ ) ; 
 int __cvmx_helper_xaui_link_set (int,int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 
 int cvmx_helper_interface_get_mode (int) ; 
 int cvmx_helper_ports_on_interface (int) ; 

int cvmx_helper_link_set(int ipd_port, cvmx_helper_link_info_t link_info)
{
	int result = -1;
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);

	if (index >= cvmx_helper_ports_on_interface(interface))
		return -1;

	switch (cvmx_helper_interface_get_mode(interface)) {
	case CVMX_HELPER_INTERFACE_MODE_DISABLED:
	case CVMX_HELPER_INTERFACE_MODE_PCIE:
		break;
	case CVMX_HELPER_INTERFACE_MODE_XAUI:
		result = __cvmx_helper_xaui_link_set(ipd_port, link_info);
		break;
		/*
		 * RGMII/GMII/MII are all treated about the same. Most
		 * functions refer to these ports as RGMII.
		 */
	case CVMX_HELPER_INTERFACE_MODE_RGMII:
	case CVMX_HELPER_INTERFACE_MODE_GMII:
		result = __cvmx_helper_rgmii_link_set(ipd_port, link_info);
		break;
	case CVMX_HELPER_INTERFACE_MODE_SPI:
		result = __cvmx_helper_spi_link_set(ipd_port, link_info);
		break;
	case CVMX_HELPER_INTERFACE_MODE_SGMII:
	case CVMX_HELPER_INTERFACE_MODE_PICMG:
		result = __cvmx_helper_sgmii_link_set(ipd_port, link_info);
		break;
	case CVMX_HELPER_INTERFACE_MODE_NPI:
	case CVMX_HELPER_INTERFACE_MODE_LOOP:
		break;
	}
	return result;
}