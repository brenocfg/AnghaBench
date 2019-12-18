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
typedef  int const u32 ;
struct intel_context {int* lrc_reg_state; } ;

/* Variables and functions */
 size_t CTX_CONTEXT_CONTROL_VAL ; 
 int /*<<< orphan*/  CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT ; 
 int _MASKED_BIT_ENABLE (int /*<<< orphan*/ ) ; 

bool is_inhibit_context(struct intel_context *ce)
{
	const u32 *reg_state = ce->lrc_reg_state;
	u32 inhibit_mask =
		_MASKED_BIT_ENABLE(CTX_CTRL_ENGINE_CTX_RESTORE_INHIBIT);

	return inhibit_mask ==
		(reg_state[CTX_CONTEXT_CONTROL_VAL] & inhibit_mask);
}