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
struct sas_identify {void* target_port_protocols; void* initiator_port_protocols; int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {struct sas_identify identify; } ;
struct hpsa_sas_port {int /*<<< orphan*/  sas_address; } ;

/* Variables and functions */
 void* SAS_PROTOCOL_STP ; 
 int sas_rphy_add (struct sas_rphy*) ; 

__attribute__((used)) static int
	hpsa_sas_port_add_rphy(struct hpsa_sas_port *hpsa_sas_port,
				struct sas_rphy *rphy)
{
	struct sas_identify *identify;

	identify = &rphy->identify;
	identify->sas_address = hpsa_sas_port->sas_address;
	identify->initiator_port_protocols = SAS_PROTOCOL_STP;
	identify->target_port_protocols = SAS_PROTOCOL_STP;

	return sas_rphy_add(rphy);
}