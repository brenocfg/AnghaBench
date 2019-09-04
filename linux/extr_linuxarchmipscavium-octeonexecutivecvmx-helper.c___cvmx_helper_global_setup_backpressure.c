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

__attribute__((used)) static int __cvmx_helper_global_setup_backpressure(void)
{
#if CVMX_HELPER_DISABLE_RGMII_BACKPRESSURE
	/* Disable backpressure if configured to do so */
	/* Disable backpressure (pause frame) generation */
	int num_interfaces = cvmx_helper_get_number_of_interfaces();
	int interface;
	for (interface = 0; interface < num_interfaces; interface++) {
		switch (cvmx_helper_interface_get_mode(interface)) {
		case CVMX_HELPER_INTERFACE_MODE_DISABLED:
		case CVMX_HELPER_INTERFACE_MODE_PCIE:
		case CVMX_HELPER_INTERFACE_MODE_NPI:
		case CVMX_HELPER_INTERFACE_MODE_LOOP:
		case CVMX_HELPER_INTERFACE_MODE_XAUI:
			break;
		case CVMX_HELPER_INTERFACE_MODE_RGMII:
		case CVMX_HELPER_INTERFACE_MODE_GMII:
		case CVMX_HELPER_INTERFACE_MODE_SPI:
		case CVMX_HELPER_INTERFACE_MODE_SGMII:
		case CVMX_HELPER_INTERFACE_MODE_PICMG:
			cvmx_gmx_set_backpressure_override(interface, 0xf);
			break;
		}
	}
#endif

	return 0;
}