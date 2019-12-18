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
struct sas_ha_struct {scalar_t__ strict_wide_ports; } ;
struct asd_sas_port {int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  attached_sas_addr; } ;
struct asd_sas_phy {int /*<<< orphan*/  sas_addr; int /*<<< orphan*/  attached_sas_addr; struct sas_ha_struct* ha; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ADDR_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool phy_is_wideport_member(struct asd_sas_port *port, struct asd_sas_phy *phy)
{
	struct sas_ha_struct *sas_ha = phy->ha;

	if (memcmp(port->attached_sas_addr, phy->attached_sas_addr,
		   SAS_ADDR_SIZE) != 0 || (sas_ha->strict_wide_ports &&
	     memcmp(port->sas_addr, phy->sas_addr, SAS_ADDR_SIZE) != 0))
		return false;
	return true;
}