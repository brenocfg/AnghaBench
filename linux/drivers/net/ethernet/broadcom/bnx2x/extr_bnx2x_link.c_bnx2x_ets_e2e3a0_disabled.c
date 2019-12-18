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
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1 ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS ; 
 int /*<<< orphan*/  NIG_REG_P0_TX_ARB_PRIORITY_CLIENT ; 
 int /*<<< orphan*/  PBF_REG_COS0_UPPER_BOUND ; 
 int /*<<< orphan*/  PBF_REG_COS0_WEIGHT ; 
 int /*<<< orphan*/  PBF_REG_COS1_UPPER_BOUND ; 
 int /*<<< orphan*/  PBF_REG_COS1_WEIGHT ; 
 int /*<<< orphan*/  PBF_REG_ETS_ENABLED ; 
 int /*<<< orphan*/  PBF_REG_HIGH_PRIORITY_COS_NUM ; 
 int /*<<< orphan*/  PBF_REG_NUM_STRICT_ARB_SLOTS ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bnx2x_ets_e2e3a0_disabled(struct link_params *params)
{
	/* ETS disabled configuration*/
	struct bnx2x *bp = params->bp;

	DP(NETIF_MSG_LINK, "ETS E2E3 disabled configuration\n");

	/* mapping between entry  priority to client number (0,1,2 -debug and
	 * management clients, 3 - COS0 client, 4 - COS client)(HIGHEST)
	 * 3bits client num.
	 *   PRI4    |    PRI3    |    PRI2    |    PRI1    |    PRI0
	 * cos1-100     cos0-011     dbg1-010     dbg0-001     MCP-000
	 */

	REG_WR(bp, NIG_REG_P0_TX_ARB_PRIORITY_CLIENT, 0x4688);
	/* Bitmap of 5bits length. Each bit specifies whether the entry behaves
	 * as strict.  Bits 0,1,2 - debug and management entries, 3 -
	 * COS0 entry, 4 - COS1 entry.
	 * COS1 | COS0 | DEBUG1 | DEBUG0 | MGMT
	 * bit4   bit3	  bit2   bit1	  bit0
	 * MCP and debug are strict
	 */

	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_STRICT, 0x7);
	/* defines which entries (clients) are subjected to WFQ arbitration */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_IS_SUBJECT2WFQ, 0);
	/* For strict priority entries defines the number of consecutive
	 * slots for the highest priority.
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_NUM_STRICT_ARB_SLOTS, 0x100);
	/* mapping between the CREDIT_WEIGHT registers and actual client
	 * numbers
	 */
	REG_WR(bp, NIG_REG_P0_TX_ARB_CLIENT_CREDIT_MAP, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_0, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_WEIGHT_1, 0);

	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_0, 0);
	REG_WR(bp, NIG_REG_P0_TX_ARB_CREDIT_UPPER_BOUND_1, 0);
	REG_WR(bp, PBF_REG_HIGH_PRIORITY_COS_NUM, 0);
	/* ETS mode disable */
	REG_WR(bp, PBF_REG_ETS_ENABLED, 0);
	/* If ETS mode is enabled (there is no strict priority) defines a WFQ
	 * weight for COS0/COS1.
	 */
	REG_WR(bp, PBF_REG_COS0_WEIGHT, 0x2710);
	REG_WR(bp, PBF_REG_COS1_WEIGHT, 0x2710);
	/* Upper bound that COS0_WEIGHT can reach in the WFQ arbiter */
	REG_WR(bp, PBF_REG_COS0_UPPER_BOUND, 0x989680);
	REG_WR(bp, PBF_REG_COS1_UPPER_BOUND, 0x989680);
	/* Defines the number of consecutive slots for the strict priority */
	REG_WR(bp, PBF_REG_NUM_STRICT_ARB_SLOTS, 0);
}