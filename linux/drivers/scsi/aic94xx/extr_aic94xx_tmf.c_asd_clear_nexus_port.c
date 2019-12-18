#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct asd_sas_port {int /*<<< orphan*/  phy_mask; TYPE_1__* ha; } ;
struct asd_ha_struct {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn_mask; int /*<<< orphan*/  nexus; } ;
struct TYPE_6__ {TYPE_2__ clear_nexus; } ;
struct TYPE_4__ {struct asd_ha_struct* lldd_ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLEAR_NEXUS_POST ; 
 int /*<<< orphan*/  CLEAR_NEXUS_PRE ; 
 int /*<<< orphan*/  NEXUS_PORT ; 
 TYPE_3__* scb ; 

int asd_clear_nexus_port(struct asd_sas_port *port)
{
	struct asd_ha_struct *asd_ha = port->ha->lldd_ha;

	CLEAR_NEXUS_PRE;
	scb->clear_nexus.nexus = NEXUS_PORT;
	scb->clear_nexus.conn_mask = port->phy_mask;
	CLEAR_NEXUS_POST;
}