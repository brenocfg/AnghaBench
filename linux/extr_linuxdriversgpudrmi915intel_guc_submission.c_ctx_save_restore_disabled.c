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
typedef  int u32 ;
struct intel_context {int* lrc_reg_state; } ;

/* Variables and functions */
 int CTX_CONTEXT_CONTROL ; 
 int CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT ; 
 int CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT ; 
 int _MASKED_BIT_ENABLE (int) ; 

__attribute__((used)) static inline bool ctx_save_restore_disabled(struct intel_context *ce)
{
	u32 sr = ce->lrc_reg_state[CTX_CONTEXT_CONTROL + 1];

#define SR_DISABLED \
	_MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT | \
			   CTX_CTRL_ENGINE_CTX_SAVE_INHIBIT)

	return (sr & SR_DISABLED) == SR_DISABLED;

#undef SR_DISABLED
}