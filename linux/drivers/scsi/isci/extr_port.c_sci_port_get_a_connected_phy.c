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
typedef  size_t u32 ;
struct isci_port {struct isci_phy** phy_table; } ;
struct isci_phy {int dummy; } ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 
 scalar_t__ sci_port_active_phy (struct isci_port*,struct isci_phy*) ; 

__attribute__((used)) static struct isci_phy *sci_port_get_a_connected_phy(struct isci_port *iport)
{
	u32 index;
	struct isci_phy *iphy;

	for (index = 0; index < SCI_MAX_PHYS; index++) {
		/* Ensure that the phy is both part of the port and currently
		 * connected to the remote end-point.
		 */
		iphy = iport->phy_table[index];
		if (iphy && sci_port_active_phy(iport, iphy))
			return iphy;
	}

	return NULL;
}