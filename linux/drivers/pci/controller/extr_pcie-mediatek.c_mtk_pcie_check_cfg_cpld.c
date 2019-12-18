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
typedef  int u32 ;
struct mtk_pcie_port {scalar_t__ base; } ;

/* Variables and functions */
 int APP_CFG_REQ ; 
 int APP_CPL_STATUS ; 
 int PCIBIOS_SET_FAILED ; 
 int PCIBIOS_SUCCESSFUL ; 
 scalar_t__ PCIE_APP_TLP_REQ ; 
 int USEC_PER_MSEC ; 
 int readl (scalar_t__) ; 
 int readl_poll_timeout_atomic (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static int mtk_pcie_check_cfg_cpld(struct mtk_pcie_port *port)
{
	u32 val;
	int err;

	err = readl_poll_timeout_atomic(port->base + PCIE_APP_TLP_REQ, val,
					!(val & APP_CFG_REQ), 10,
					100 * USEC_PER_MSEC);
	if (err)
		return PCIBIOS_SET_FAILED;

	if (readl(port->base + PCIE_APP_TLP_REQ) & APP_CPL_STATUS)
		return PCIBIOS_SET_FAILED;

	return PCIBIOS_SUCCESSFUL;
}