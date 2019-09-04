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
struct altera_jtag {scalar_t__ jtag_state; int /*<<< orphan*/ * ir_buffer; int /*<<< orphan*/ * ir_post_data; int /*<<< orphan*/ * ir_pre_data; int /*<<< orphan*/ * dr_buffer; int /*<<< orphan*/ * dr_post_data; int /*<<< orphan*/ * dr_pre_data; } ;
struct altera_state {struct altera_jtag js; } ;

/* Variables and functions */
 scalar_t__ ILLEGAL_JTAG_STATE ; 
 int /*<<< orphan*/  altera_jreset_idle (struct altera_state*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void altera_free_buffers(struct altera_state *astate)
{
	struct altera_jtag *js = &astate->js;
	/* If the JTAG interface was used, reset it to TLR */
	if (js->jtag_state != ILLEGAL_JTAG_STATE)
		altera_jreset_idle(astate);

	kfree(js->dr_pre_data);
	js->dr_pre_data = NULL;

	kfree(js->dr_post_data);
	js->dr_post_data = NULL;

	kfree(js->dr_buffer);
	js->dr_buffer = NULL;

	kfree(js->ir_pre_data);
	js->ir_pre_data = NULL;

	kfree(js->ir_post_data);
	js->ir_post_data = NULL;

	kfree(js->ir_buffer);
	js->ir_buffer = NULL;
}