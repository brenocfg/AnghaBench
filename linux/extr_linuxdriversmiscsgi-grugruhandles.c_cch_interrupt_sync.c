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
struct gru_context_configuration_handle {int /*<<< orphan*/  opc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCHOP_INTERRUPT_SYNC ; 
 int /*<<< orphan*/  cchop_interrupt_sync ; 
 int /*<<< orphan*/  start_instruction (struct gru_context_configuration_handle*) ; 
 int wait_instruction_complete (struct gru_context_configuration_handle*,int /*<<< orphan*/ ) ; 

int cch_interrupt_sync(struct gru_context_configuration_handle
				     *cch)
{
	cch->opc = CCHOP_INTERRUPT_SYNC;
	start_instruction(cch);
	return wait_instruction_complete(cch, cchop_interrupt_sync);
}