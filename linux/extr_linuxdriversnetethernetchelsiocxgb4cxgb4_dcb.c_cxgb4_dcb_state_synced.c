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
typedef  enum cxgb4_dcb_state { ____Placeholder_cxgb4_dcb_state } cxgb4_dcb_state ;

/* Variables and functions */
 int CXGB4_DCB_STATE_FW_ALLSYNCED ; 
 int CXGB4_DCB_STATE_HOST ; 

__attribute__((used)) static inline bool cxgb4_dcb_state_synced(enum cxgb4_dcb_state state)
{
	if (state == CXGB4_DCB_STATE_FW_ALLSYNCED ||
	    state == CXGB4_DCB_STATE_HOST)
		return true;
	else
		return false;
}