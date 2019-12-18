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
struct tb_port {int /*<<< orphan*/  cap_adap; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int TB_PCI_EN ; 
 int tb_port_write (struct tb_port*,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int tb_pci_port_enable(struct tb_port *port, bool enable)
{
	u32 word = enable ? TB_PCI_EN : 0x0;
	if (!port->cap_adap)
		return -ENXIO;
	return tb_port_write(port, &word, TB_CFG_PORT, port->cap_adap, 1);
}