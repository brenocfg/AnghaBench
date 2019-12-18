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
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_AGENCTRL ; 
 int ANA_AGENCTRL_IGNORE_DMAC_FLAGS ; 
 int ANA_AGENCTRL_LEARN_CPU_COPY ; 
 int ANA_AGENCTRL_LEARN_FWD_KILL ; 
 int ANA_AGENCTRL_LEARN_IGNORE_VLAN ; 
 int /*<<< orphan*/  ANA_TABLES_MACACCESS ; 
 int /*<<< orphan*/  MACACCESS_CMD_INIT ; 
 int /*<<< orphan*/  ocelot_rmw (struct ocelot*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocelot_mact_init(struct ocelot *ocelot)
{
	/* Configure the learning mode entries attributes:
	 * - Do not copy the frame to the CPU extraction queues.
	 * - Use the vlan and mac_cpoy for dmac lookup.
	 */
	ocelot_rmw(ocelot, 0,
		   ANA_AGENCTRL_LEARN_CPU_COPY | ANA_AGENCTRL_IGNORE_DMAC_FLAGS
		   | ANA_AGENCTRL_LEARN_FWD_KILL
		   | ANA_AGENCTRL_LEARN_IGNORE_VLAN,
		   ANA_AGENCTRL);

	/* Clear the MAC table */
	ocelot_write(ocelot, MACACCESS_CMD_INIT, ANA_TABLES_MACACCESS);
}