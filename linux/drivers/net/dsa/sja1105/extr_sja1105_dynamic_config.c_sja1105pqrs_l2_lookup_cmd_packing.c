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
typedef  void u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct sja1105_dyn_cmd {int /*<<< orphan*/  index; int /*<<< orphan*/  valident; scalar_t__ search; int /*<<< orphan*/  rdwrset; int /*<<< orphan*/  errors; int /*<<< orphan*/  valid; } ;
typedef  enum packing_op { ____Placeholder_packing_op } packing_op ;

/* Variables and functions */
 int SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY ; 
 int /*<<< orphan*/  SJA1105_HOSTCMD_INVALIDATE ; 
 int /*<<< orphan*/  SJA1105_HOSTCMD_READ ; 
 int /*<<< orphan*/  SJA1105_HOSTCMD_SEARCH ; 
 int /*<<< orphan*/  SJA1105_HOSTCMD_WRITE ; 
 int SJA1105_SIZE_DYN_CMD ; 
 int /*<<< orphan*/  SPI_READ ; 
 int /*<<< orphan*/  sja1105_packing (void*,int /*<<< orphan*/ *,int,int,int const,int) ; 

__attribute__((used)) static void
sja1105pqrs_l2_lookup_cmd_packing(void *buf, struct sja1105_dyn_cmd *cmd,
				  enum packing_op op)
{
	u8 *p = buf + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	const int size = SJA1105_SIZE_DYN_CMD;
	u64 hostcmd;

	sja1105_packing(p, &cmd->valid,    31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset,  30, 30, size, op);
	sja1105_packing(p, &cmd->errors,   29, 29, size, op);
	sja1105_packing(p, &cmd->valident, 27, 27, size, op);

	/* VALIDENT is supposed to indicate "keep or not", but in SJA1105 E/T,
	 * using it to delete a management route was unsupported. UM10944
	 * said about it:
	 *
	 *   In case of a write access with the MGMTROUTE flag set,
	 *   the flag will be ignored. It will always be found cleared
	 *   for read accesses with the MGMTROUTE flag set.
	 *
	 * SJA1105 P/Q/R/S keeps the same behavior w.r.t. VALIDENT, but there
	 * is now another flag called HOSTCMD which does more stuff (quoting
	 * from UM11040):
	 *
	 *   A write request is accepted only when HOSTCMD is set to write host
	 *   or invalid. A read request is accepted only when HOSTCMD is set to
	 *   search host or read host.
	 *
	 * So it is possible to translate a RDWRSET/VALIDENT combination into
	 * HOSTCMD so that we keep the dynamic command API in place, and
	 * at the same time achieve compatibility with the management route
	 * command structure.
	 */
	if (cmd->rdwrset == SPI_READ) {
		if (cmd->search)
			hostcmd = SJA1105_HOSTCMD_SEARCH;
		else
			hostcmd = SJA1105_HOSTCMD_READ;
	} else {
		/* SPI_WRITE */
		if (cmd->valident)
			hostcmd = SJA1105_HOSTCMD_WRITE;
		else
			hostcmd = SJA1105_HOSTCMD_INVALIDATE;
	}
	sja1105_packing(p, &hostcmd, 25, 23, size, op);

	/* Hack - The hardware takes the 'index' field within
	 * struct sja1105_l2_lookup_entry as the index on which this command
	 * will operate. However it will ignore everything else, so 'index'
	 * is logically part of command but physically part of entry.
	 * Populate the 'index' entry field from within the command callback,
	 * such that our API doesn't need to ask for a full-blown entry
	 * structure when e.g. a delete is requested.
	 */
	sja1105_packing(buf, &cmd->index, 15, 6,
			SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY, op);
}