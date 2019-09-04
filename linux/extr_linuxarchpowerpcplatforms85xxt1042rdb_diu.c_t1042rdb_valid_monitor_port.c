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
typedef  enum fsl_diu_monitor_port { ____Placeholder_fsl_diu_monitor_port } fsl_diu_monitor_port ;

/* Variables and functions */
#define  FSL_DIU_PORT_DVI 129 
#define  FSL_DIU_PORT_LVDS 128 

__attribute__((used)) static enum fsl_diu_monitor_port
t1042rdb_valid_monitor_port(enum fsl_diu_monitor_port port)
{
	switch (port) {
	case FSL_DIU_PORT_DVI:
	case FSL_DIU_PORT_LVDS:
		return port;
	default:
		return FSL_DIU_PORT_DVI; /* Dual-link LVDS is not supported */
	}
}