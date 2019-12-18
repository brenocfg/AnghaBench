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
struct ocelot_port {int /*<<< orphan*/  chip_port; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_PORT_VCAP_S2_CFG ; 
 int ANA_PORT_VCAP_S2_CFG_S2_ENA ; 
 int ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG (int) ; 
 int /*<<< orphan*/  ocelot_write_gix (struct ocelot*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_vcap_enable(struct ocelot *ocelot, struct ocelot_port *port)
{
	ocelot_write_gix(ocelot, ANA_PORT_VCAP_S2_CFG_S2_ENA |
			 ANA_PORT_VCAP_S2_CFG_S2_IP6_CFG(0xa),
			 ANA_PORT_VCAP_S2_CFG, port->chip_port);
}