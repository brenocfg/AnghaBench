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
typedef  int u32 ;
struct ocelot_port {int chip_port; struct ocelot* ocelot; } ;
struct ocelot_mact_entry {int vid; int /*<<< orphan*/  mac; } ;
struct ocelot {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANA_TABLES_MACACCESS ; 
 int ANA_TABLES_MACACCESS_DEST_IDX_M ; 
 int /*<<< orphan*/  ANA_TABLES_MACACCESS_MAC_TABLE_CMD (int /*<<< orphan*/ ) ; 
 int ANA_TABLES_MACACCESS_VALID ; 
 int /*<<< orphan*/  ANA_TABLES_MACHDATA ; 
 int /*<<< orphan*/  ANA_TABLES_MACLDATA ; 
 int /*<<< orphan*/  ANA_TABLES_MACTINDX_BUCKET ; 
 int /*<<< orphan*/  ANA_TABLES_MACTINDX_M_INDEX ; 
 int EINVAL ; 
 int ETH_ALEN ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MACACCESS_CMD_READ ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ocelot_field_write (struct ocelot*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ocelot_mact_wait_for_completion (struct ocelot*) ; 
 int ocelot_read (struct ocelot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocelot_write (struct ocelot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocelot_mact_read(struct ocelot_port *port, int row, int col,
				   struct ocelot_mact_entry *entry)
{
	struct ocelot *ocelot = port->ocelot;
	char mac[ETH_ALEN];
	u32 val, dst, macl, mach;

	/* Set row and column to read from */
	ocelot_field_write(ocelot, ANA_TABLES_MACTINDX_M_INDEX, row);
	ocelot_field_write(ocelot, ANA_TABLES_MACTINDX_BUCKET, col);

	/* Issue a read command */
	ocelot_write(ocelot,
		     ANA_TABLES_MACACCESS_MAC_TABLE_CMD(MACACCESS_CMD_READ),
		     ANA_TABLES_MACACCESS);

	if (ocelot_mact_wait_for_completion(ocelot))
		return -ETIMEDOUT;

	/* Read the entry flags */
	val = ocelot_read(ocelot, ANA_TABLES_MACACCESS);
	if (!(val & ANA_TABLES_MACACCESS_VALID))
		return -EINVAL;

	/* If the entry read has another port configured as its destination,
	 * do not report it.
	 */
	dst = (val & ANA_TABLES_MACACCESS_DEST_IDX_M) >> 3;
	if (dst != port->chip_port)
		return -EINVAL;

	/* Get the entry's MAC address and VLAN id */
	macl = ocelot_read(ocelot, ANA_TABLES_MACLDATA);
	mach = ocelot_read(ocelot, ANA_TABLES_MACHDATA);

	mac[0] = (mach >> 8)  & 0xff;
	mac[1] = (mach >> 0)  & 0xff;
	mac[2] = (macl >> 24) & 0xff;
	mac[3] = (macl >> 16) & 0xff;
	mac[4] = (macl >> 8)  & 0xff;
	mac[5] = (macl >> 0)  & 0xff;

	entry->vid = (mach >> 16) & 0xfff;
	ether_addr_copy(entry->mac, mac);

	return 0;
}