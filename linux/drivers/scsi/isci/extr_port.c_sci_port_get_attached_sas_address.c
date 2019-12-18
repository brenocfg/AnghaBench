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
struct sci_sas_address {scalar_t__ low; scalar_t__ high; } ;
struct isci_port {int dummy; } ;
struct isci_phy {scalar_t__ protocol; scalar_t__ phy_index; } ;

/* Variables and functions */
 scalar_t__ SAS_PROTOCOL_SATA ; 
 int /*<<< orphan*/  sci_phy_get_attached_sas_address (struct isci_phy*,struct sci_sas_address*) ; 
 int /*<<< orphan*/  sci_phy_get_sas_address (struct isci_phy*,struct sci_sas_address*) ; 
 struct isci_phy* sci_port_get_a_connected_phy (struct isci_port*) ; 

void sci_port_get_attached_sas_address(struct isci_port *iport, struct sci_sas_address *sas)
{
	struct isci_phy *iphy;

	/*
	 * Ensure that the phy is both part of the port and currently
	 * connected to the remote end-point.
	 */
	iphy = sci_port_get_a_connected_phy(iport);
	if (iphy) {
		if (iphy->protocol != SAS_PROTOCOL_SATA) {
			sci_phy_get_attached_sas_address(iphy, sas);
		} else {
			sci_phy_get_sas_address(iphy, sas);
			sas->low += iphy->phy_index;
		}
	} else {
		sas->high = 0;
		sas->low  = 0;
	}
}