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
 scalar_t__ CVMX_BOARD_TYPE_SIM ; 
 int /*<<< orphan*/  __cvmx_helper_setup_gmx (int,int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_hardware_init_one_time (int,int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_link_get (int) ; 
 int /*<<< orphan*/  __cvmx_helper_sgmii_link_set (int,int /*<<< orphan*/ ) ; 
 int cvmx_helper_get_ipd_port (int,int) ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

__attribute__((used)) static int __cvmx_helper_sgmii_hardware_init(int interface, int num_ports)
{
	int index;

	__cvmx_helper_setup_gmx(interface, num_ports);

	for (index = 0; index < num_ports; index++) {
		int ipd_port = cvmx_helper_get_ipd_port(interface, index);
		__cvmx_helper_sgmii_hardware_init_one_time(interface, index);
		/* Linux kernel driver will call ....link_set with the
		 * proper link state. In the simulator there is no
		 * link state polling and hence it is set from
		 * here.
		 */
		if (cvmx_sysinfo_get()->board_type == CVMX_BOARD_TYPE_SIM)
			__cvmx_helper_sgmii_link_set(ipd_port,
				       __cvmx_helper_sgmii_link_get(ipd_port));
	}

	return 0;
}