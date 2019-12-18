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
typedef  size_t u8 ;
struct sci_phy_proto {scalar_t__ all; } ;
struct isci_port {struct isci_phy** phy_table; } ;
struct isci_phy {int dummy; } ;

/* Variables and functions */
 size_t SCI_MAX_PHYS ; 
 int /*<<< orphan*/  sci_phy_get_protocols (struct isci_phy*,struct sci_phy_proto*) ; 

__attribute__((used)) static void sci_port_get_protocols(struct isci_port *iport, struct sci_phy_proto *proto)
{
	u8 index;

	proto->all = 0;
	for (index = 0; index < SCI_MAX_PHYS; index++) {
		struct isci_phy *iphy = iport->phy_table[index];

		if (!iphy)
			continue;
		sci_phy_get_protocols(iphy, proto);
	}
}