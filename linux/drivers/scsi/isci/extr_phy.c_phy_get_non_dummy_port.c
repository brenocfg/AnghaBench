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
struct isci_port {scalar_t__ physical_port_index; } ;
struct isci_phy {struct isci_port* owning_port; } ;

/* Variables and functions */
 scalar_t__ SCIC_SDS_DUMMY_PORT ; 

struct isci_port *phy_get_non_dummy_port(struct isci_phy *iphy)
{
	struct isci_port *iport = iphy->owning_port;

	if (iport->physical_port_index == SCIC_SDS_DUMMY_PORT)
		return NULL;

	return iphy->owning_port;
}