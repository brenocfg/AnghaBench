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
struct sas_identify {void* target_port_protocols; void* initiator_port_protocols; int /*<<< orphan*/  sas_address; } ;
struct sas_rphy {struct sas_identify identify; } ;
struct pqi_sas_port {TYPE_1__* device; int /*<<< orphan*/  sas_address; } ;
struct TYPE_2__ {scalar_t__ is_expander_smp_device; } ;

/* Variables and functions */
 void* SAS_PROTOCOL_SMP ; 
 void* SAS_PROTOCOL_STP ; 
 int sas_rphy_add (struct sas_rphy*) ; 

__attribute__((used)) static int pqi_sas_port_add_rphy(struct pqi_sas_port *pqi_sas_port,
	struct sas_rphy *rphy)
{
	struct sas_identify *identify;

	identify = &rphy->identify;
	identify->sas_address = pqi_sas_port->sas_address;

	if (pqi_sas_port->device &&
		pqi_sas_port->device->is_expander_smp_device) {
		identify->initiator_port_protocols = SAS_PROTOCOL_SMP;
		identify->target_port_protocols = SAS_PROTOCOL_SMP;
	} else {
		identify->initiator_port_protocols = SAS_PROTOCOL_STP;
		identify->target_port_protocols = SAS_PROTOCOL_STP;
	}

	return sas_rphy_add(rphy);
}