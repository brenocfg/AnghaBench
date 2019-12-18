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
struct mt7621_pcie_port {int dummy; } ;

/* Variables and functions */
 int PCIE_PORT_LINKUP ; 
 int /*<<< orphan*/  RALINK_PCI_STATUS ; 
 int pcie_port_read (struct mt7621_pcie_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool mt7621_pcie_port_is_linkup(struct mt7621_pcie_port *port)
{
	return (pcie_port_read(port, RALINK_PCI_STATUS) & PCIE_PORT_LINKUP) != 0;
}