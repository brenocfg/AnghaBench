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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct rio_mport {int dummy; } ;

/* Variables and functions */
 int IDT_DEFAULT_ROUTE ; 
 int /*<<< orphan*/  LOCAL_RTE_CONF_DESTID_SEL ; 
 scalar_t__ RIO_GLOBAL_TABLE ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_DESTID_SEL_CSR ; 
 int RIO_STD_RTE_CONF_EXTCFGEN ; 
 int /*<<< orphan*/  RIO_STD_RTE_CONF_PORT_SEL_CSR ; 
 int /*<<< orphan*/  rio_mport_write_config_32 (struct rio_mport*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
idtg2_route_clr_table(struct rio_mport *mport, u16 destid, u8 hopcount,
		       u16 table)
{
	u32 i;

	/*
	 * Select routing table to read
	 */
	if (table == RIO_GLOBAL_TABLE)
		table = 0;
	else
		table++;

	rio_mport_write_config_32(mport, destid, hopcount,
				  LOCAL_RTE_CONF_DESTID_SEL, table);

	for (i = RIO_STD_RTE_CONF_EXTCFGEN;
	     i <= (RIO_STD_RTE_CONF_EXTCFGEN | 0xff);) {
		rio_mport_write_config_32(mport, destid, hopcount,
			RIO_STD_RTE_CONF_DESTID_SEL_CSR, i);
		rio_mport_write_config_32(mport, destid, hopcount,
			RIO_STD_RTE_CONF_PORT_SEL_CSR,
			(IDT_DEFAULT_ROUTE << 24) | (IDT_DEFAULT_ROUTE << 16) |
			(IDT_DEFAULT_ROUTE << 8) | IDT_DEFAULT_ROUTE);
		i += 4;
	}

	return 0;
}