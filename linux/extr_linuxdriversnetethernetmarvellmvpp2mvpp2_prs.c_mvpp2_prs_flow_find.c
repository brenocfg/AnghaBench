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
typedef  int u8 ;
struct mvpp2_prs_entry {int dummy; } ;
struct mvpp2 {TYPE_1__* prs_shadow; } ;
struct TYPE_2__ {scalar_t__ lu; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int ENOENT ; 
 int MVPP2_PRS_FLOW_ID_MASK ; 
 scalar_t__ MVPP2_PRS_LU_FLOWS ; 
 int MVPP2_PRS_TCAM_SRAM_SIZE ; 
 int /*<<< orphan*/  mvpp2_prs_init_from_hw (struct mvpp2*,struct mvpp2_prs_entry*,int) ; 
 int mvpp2_prs_sram_ai_get (struct mvpp2_prs_entry*) ; 

__attribute__((used)) static int mvpp2_prs_flow_find(struct mvpp2 *priv, int flow)
{
	struct mvpp2_prs_entry pe;
	int tid;

	/* Go through the all entires with MVPP2_PRS_LU_FLOWS */
	for (tid = MVPP2_PRS_TCAM_SRAM_SIZE - 1; tid >= 0; tid--) {
		u8 bits;

		if (!priv->prs_shadow[tid].valid ||
		    priv->prs_shadow[tid].lu != MVPP2_PRS_LU_FLOWS)
			continue;

		mvpp2_prs_init_from_hw(priv, &pe, tid);
		bits = mvpp2_prs_sram_ai_get(&pe);

		/* Sram store classification lookup ID in AI bits [5:0] */
		if ((bits & MVPP2_PRS_FLOW_ID_MASK) == flow)
			return tid;
	}

	return -ENOENT;
}