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
struct sas_rphy {int dummy; } ;
struct pqi_sas_port {int /*<<< orphan*/  port; TYPE_1__* device; } ;
struct TYPE_2__ {scalar_t__ is_expander_smp_device; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_FANOUT_EXPANDER_DEVICE ; 
 struct sas_rphy* sas_end_device_alloc (int /*<<< orphan*/ ) ; 
 struct sas_rphy* sas_expander_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sas_rphy *pqi_sas_rphy_alloc(struct pqi_sas_port *pqi_sas_port)
{
	if (pqi_sas_port->device &&
		pqi_sas_port->device->is_expander_smp_device)
		return sas_expander_alloc(pqi_sas_port->port,
				SAS_FANOUT_EXPANDER_DEVICE);

	return sas_end_device_alloc(pqi_sas_port->port);
}