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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
union cvmx_gmxx_inf_mode {TYPE_1__ cn68xx; int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  cvmx_helper_interface_mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_GMXX_INF_MODE (int) ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_DISABLED ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_LOOP ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_NPI ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  CVMX_HELPER_INTERFACE_MODE_XAUI ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static cvmx_helper_interface_mode_t __cvmx_get_mode_cn7xxx(int interface)
{
	union cvmx_gmxx_inf_mode mode;

	mode.u64 = cvmx_read_csr(CVMX_GMXX_INF_MODE(interface));

	switch (interface) {
	case 0:
	case 1:
		switch (mode.cn68xx.mode) {
		case 0:
			return CVMX_HELPER_INTERFACE_MODE_DISABLED;
		case 1:
		case 2:
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		case 3:
			return CVMX_HELPER_INTERFACE_MODE_XAUI;
		default:
			return CVMX_HELPER_INTERFACE_MODE_SGMII;
		}
	case 2:
		return CVMX_HELPER_INTERFACE_MODE_NPI;
	case 3:
		return CVMX_HELPER_INTERFACE_MODE_LOOP;
	case 4:
		/* TODO: Implement support for AGL (RGMII). */
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	default:
		return CVMX_HELPER_INTERFACE_MODE_DISABLED;
	}
}