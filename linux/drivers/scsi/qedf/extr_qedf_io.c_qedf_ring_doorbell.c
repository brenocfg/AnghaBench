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
struct qedf_rport {int /*<<< orphan*/  p_doorbell; int /*<<< orphan*/  fw_sq_prod_idx; } ;
struct fcoe_db_data {int params; int /*<<< orphan*/  sq_prod; scalar_t__ agg_flags; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int DB_AGG_CMD_SET ; 
 int DB_DEST_XCM ; 
 int DQ_XCM_FCOE_SQ_PROD_CMD ; 
 int FCOE_DB_DATA_AGG_CMD_SHIFT ; 
 int FCOE_DB_DATA_AGG_VAL_SEL_SHIFT ; 
 int FCOE_DB_DATA_DEST_SHIFT ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void qedf_ring_doorbell(struct qedf_rport *fcport)
{
	struct fcoe_db_data dbell = { 0 };

	dbell.agg_flags = 0;

	dbell.params |= DB_DEST_XCM << FCOE_DB_DATA_DEST_SHIFT;
	dbell.params |= DB_AGG_CMD_SET << FCOE_DB_DATA_AGG_CMD_SHIFT;
	dbell.params |= DQ_XCM_FCOE_SQ_PROD_CMD <<
	    FCOE_DB_DATA_AGG_VAL_SEL_SHIFT;

	dbell.sq_prod = fcport->fw_sq_prod_idx;
	/* wmb makes sure that the BDs data is updated before updating the
	 * producer, otherwise FW may read old data from the BDs.
	 */
	wmb();
	barrier();
	writel(*(u32 *)&dbell, fcport->p_doorbell);
	/*
	 * Fence required to flush the write combined buffer, since another
	 * CPU may write to the same doorbell address and data may be lost
	 * due to relaxed order nature of write combined bar.
	 */
	wmb();
}