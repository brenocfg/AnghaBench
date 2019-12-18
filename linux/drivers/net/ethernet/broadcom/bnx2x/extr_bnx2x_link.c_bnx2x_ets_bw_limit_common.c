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
struct link_params {struct bnx2x* bp; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int ETS_BW_LIMIT_CREDIT_UPPER_BOUND ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1 ; 
 int /*<<< orphan*/  PBF_REG_COS0_UPPER_BOUND ; 
 int /*<<< orphan*/  PBF_REG_COS1_UPPER_BOUND ; 
 int /*<<< orphan*/  PBF_REG_ETS_ENABLED ; 
 int /*<<< orphan*/  PBF_REG_NUM_STRICT_ARB_SLOTS ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_ets_bw_limit_common(const struct link_params *params)
{
	/* ETS disabled configuration */
	struct bnx2x *bp = params->bp;
	DP(NETIF_MSG_LINK, "ETS enabled BW limit configuration\n");
	/* Defines which entries (clients) are subjected to WFQ arbitration
	 * COS0 0x8
	 * COS1 0x10
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0x18);
	/* Mapping between the ARB_CREDIT_WEIGHT registers and actual
	 * client numbers (WEIGHT_0 does not actually have to represent
	 * client 0)
	 *    PRI4    |    PRI3    |    PRI2    |    PRI1    |    PRI0
	 *  cos1-001     cos0-000     dbg1-100     dbg0-011     MCP-010
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP, 0x111A);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);

	/* ETS mode enabled*/
	REG_WR(bp, PBF_REG_ETS_ENABLED, 1);

	/* Defines the number of consecutive slots for the strict priority */
	REG_WR(bp, PBF_REG_NUM_STRICT_ARB_SLOTS, 0);
	/* Bitmap of 5bits length. Each bit specifies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 - COS0
	 * entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG21 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2     bit1	   bit0
	 * MCP and debug are strict
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x7);

	/* Upper bound that COS0_WEIGHT can reach in the WFQ arbiter.*/
	REG_WR(bp, PBF_REG_COS0_UPPER_BOUND,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
	REG_WR(bp, PBF_REG_COS1_UPPER_BOUND,
	       ETS_BW_LIMIT_CREDIT_UPPER_BOUND);
}