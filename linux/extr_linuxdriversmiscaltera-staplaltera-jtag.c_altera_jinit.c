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
struct altera_jtag {int /*<<< orphan*/ * ir_buffer; int /*<<< orphan*/ * dr_buffer; int /*<<< orphan*/ * ir_post_data; int /*<<< orphan*/ * ir_pre_data; int /*<<< orphan*/ * dr_post_data; int /*<<< orphan*/ * dr_pre_data; scalar_t__ ir_length; scalar_t__ dr_length; scalar_t__ ir_post; scalar_t__ ir_pre; scalar_t__ dr_post; scalar_t__ dr_pre; void* irstop_state; void* drstop_state; int /*<<< orphan*/  jtag_state; } ;
struct altera_state {struct altera_jtag js; } ;

/* Variables and functions */
 void* IDLE ; 
 int /*<<< orphan*/  ILLEGAL_JTAG_STATE ; 

int altera_jinit(struct altera_state *astate)
{
	struct altera_jtag *js = &astate->js;

	/* initial JTAG state is unknown */
	js->jtag_state = ILLEGAL_JTAG_STATE;

	/* initialize to default state */
	js->drstop_state = IDLE;
	js->irstop_state = IDLE;
	js->dr_pre  = 0;
	js->dr_post = 0;
	js->ir_pre  = 0;
	js->ir_post = 0;
	js->dr_length    = 0;
	js->ir_length    = 0;

	js->dr_pre_data  = NULL;
	js->dr_post_data = NULL;
	js->ir_pre_data  = NULL;
	js->ir_post_data = NULL;
	js->dr_buffer	 = NULL;
	js->ir_buffer	 = NULL;

	return 0;
}