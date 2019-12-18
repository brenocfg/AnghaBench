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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int error_event_table_tlv_status; scalar_t__* lmac_error_event_table; } ;
struct iwl_trans {TYPE_1__ dbg; } ;

/* Variables and functions */
 int IWL_ERROR_EVENT_TABLE_LMAC1 ; 
 scalar_t__ WARN_ON (int) ; 

__attribute__((used)) static inline void iwl_fw_lmac1_set_alive_err_table(struct iwl_trans *trans,
						    u32 lmac_error_event_table)
{
	if (!(trans->dbg.error_event_table_tlv_status &
	      IWL_ERROR_EVENT_TABLE_LMAC1) ||
	    WARN_ON(trans->dbg.lmac_error_event_table[0] !=
		    lmac_error_event_table))
		trans->dbg.lmac_error_event_table[0] = lmac_error_event_table;
}