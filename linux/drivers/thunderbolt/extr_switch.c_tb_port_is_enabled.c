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
struct TYPE_2__ {int type; } ;
struct tb_port {TYPE_1__ config; } ;

/* Variables and functions */
#define  TB_TYPE_DP_HDMI_IN 131 
#define  TB_TYPE_DP_HDMI_OUT 130 
#define  TB_TYPE_PCIE_DOWN 129 
#define  TB_TYPE_PCIE_UP 128 
 int tb_dp_port_is_enabled (struct tb_port*) ; 
 int tb_pci_port_is_enabled (struct tb_port*) ; 

bool tb_port_is_enabled(struct tb_port *port)
{
	switch (port->config.type) {
	case TB_TYPE_PCIE_UP:
	case TB_TYPE_PCIE_DOWN:
		return tb_pci_port_is_enabled(port);

	case TB_TYPE_DP_HDMI_IN:
	case TB_TYPE_DP_HDMI_OUT:
		return tb_dp_port_is_enabled(port);

	default:
		return false;
	}
}