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
struct iwl_mvm {int dummy; } ;

/* Variables and functions */
 int IWL_MVM_RS_TPC_TX_POWER_STEP ; 
 int TPC_INVALID ; 
 int TPC_MAX_REDUCTION ; 

__attribute__((used)) static void rs_get_adjacent_txp(struct iwl_mvm *mvm, int index,
				int *weaker, int *stronger)
{
	*weaker = index + IWL_MVM_RS_TPC_TX_POWER_STEP;
	if (*weaker > TPC_MAX_REDUCTION)
		*weaker = TPC_INVALID;

	*stronger = index - IWL_MVM_RS_TPC_TX_POWER_STEP;
	if (*stronger < 0)
		*stronger = TPC_INVALID;
}