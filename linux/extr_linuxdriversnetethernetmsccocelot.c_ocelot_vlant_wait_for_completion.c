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
 int /*<<< orphan*/  ANA_TABLES_VLANACCESS ; 
 unsigned int ANA_TABLES_VLANACCESS_CMD_IDLE ; 
 unsigned int ANA_TABLES_VLANACCESS_VLAN_TBL_CMD_M ; 
 int ETIMEDOUT ; 
 unsigned int ocelot_read (struct ocelot*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ocelot_vlant_wait_for_completion(struct ocelot *ocelot)
{
	unsigned int val, timeout = 10;

	/* Wait for the issued vlan table command to be completed, or timeout.
	 * When the command read from ANA_TABLES_VLANACCESS is
	 * VLANACCESS_CMD_IDLE, the issued command completed successfully.
	 */
	do {
		val = ocelot_read(ocelot, ANA_TABLES_VLANACCESS);
		val &= ANA_TABLES_VLANACCESS_VLAN_TBL_CMD_M;
	} while (val != ANA_TABLES_VLANACCESS_CMD_IDLE && timeout--);

	if (!timeout)
		return -ETIMEDOUT;

	return 0;
}