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
typedef  int u32 ;
struct TYPE_2__ {int shmem_base; } ;
struct bnx2x {TYPE_1__ common; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ERR (char*) ; 
 size_t BP_PORT (struct bnx2x*) ; 
 int ENODEV ; 
 int MCP_ONE_TIMEOUT ; 
 int MCP_TIMEOUT ; 
 int /*<<< orphan*/  MISC_REG_SHARED_MEM_ADDR ; 
 int /*<<< orphan*/  NO_MCP_FLAG ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SHMEM_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int SHR_MEM_VALIDITY_MB ; 
 int /*<<< orphan*/  bnx2x_mcp_wait_one (struct bnx2x*) ; 
 int /*<<< orphan*/ * validity_map ; 

__attribute__((used)) static int bnx2x_init_shmem(struct bnx2x *bp)
{
	int cnt = 0;
	u32 val = 0;

	do {
		bp->common.shmem_base = REG_RD(bp, MISC_REG_SHARED_MEM_ADDR);

		/* If we read all 0xFFs, means we are in PCI error state and
		 * should bail out to avoid crashes on adapter's FW reads.
		 */
		if (bp->common.shmem_base == 0xFFFFFFFF) {
			bp->flags |= NO_MCP_FLAG;
			return -ENODEV;
		}

		if (bp->common.shmem_base) {
			val = SHMEM_RD(bp, validity_map[BP_PORT(bp)]);
			if (val & SHR_MEM_VALIDITY_MB)
				return 0;
		}

		bnx2x_mcp_wait_one(bp);

	} while (cnt++ < (MCP_TIMEOUT / MCP_ONE_TIMEOUT));

	BNX2X_ERR("BAD MCP validity signature\n");

	return -ENODEV;
}