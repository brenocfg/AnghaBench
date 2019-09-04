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
 int /*<<< orphan*/  __cvmx_helper_sgmii_hardware_init_link (int,int) ; 
 int __cvmx_helper_sgmii_hardware_init_link_speed (int,int,int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_interface_index_num (int) ; 
 int cvmx_helper_get_interface_num (int) ; 

int __cvmx_helper_sgmii_link_set(int ipd_port,
				 cvmx_helper_link_info_t link_info)
{
	int interface = cvmx_helper_get_interface_num(ipd_port);
	int index = cvmx_helper_get_interface_index_num(ipd_port);
	__cvmx_helper_sgmii_hardware_init_link(interface, index);
	return __cvmx_helper_sgmii_hardware_init_link_speed(interface, index,
							    link_info);
}