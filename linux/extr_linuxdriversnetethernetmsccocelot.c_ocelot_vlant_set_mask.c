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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_TABLES_VLANACCESS ; 
 int ANA_TABLES_VLANACCESS_CMD_WRITE ; 
 int ANA_TABLES_VLANACCESS_VLAN_PORT_MASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ANA_TABLES_VLANTIDX ; 
 int ANA_TABLES_VLANTIDX_V_INDEX (int /*<<< orphan*/ ) ; 
 int ocelot_vlant_wait_for_completion (struct ocelot*) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocelot_vlant_set_mask(struct ocelot *ocelot, u16 vid, u32 mask)
{
	/* Select the VID to configure */
	ocelot_write(ocelot, ANA_TABLES_VLANTIDX_V_INDEX(vid),
		     ANA_TABLES_VLANTIDX);
	/* Set the vlan port members mask and issue a write command */
	ocelot_write(ocelot, ANA_TABLES_VLANACCESS_VLAN_PORT_MASK(mask) |
			     ANA_TABLES_VLANACCESS_CMD_WRITE,
		     ANA_TABLES_VLANACCESS);

	return ocelot_vlant_wait_for_completion(ocelot);
}