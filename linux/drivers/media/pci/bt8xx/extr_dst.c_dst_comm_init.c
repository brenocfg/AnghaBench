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
struct dst_state {int type_flags; } ;

/* Variables and functions */
 int DST_TYPE_HAS_FW_1 ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 scalar_t__ dst_pio_enable (struct dst_state*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ rdc_reset_state (struct dst_state*) ; 

int dst_comm_init(struct dst_state *state)
{
	dprintk(2, "Initializing DST.\n");
	if ((dst_pio_enable(state)) < 0) {
		pr_err("PIO Enable Failed\n");
		return -1;
	}
	if ((rdc_reset_state(state)) < 0) {
		pr_err("RDC 8820 State RESET Failed.\n");
		return -1;
	}
	if (state->type_flags & DST_TYPE_HAS_FW_1)
		msleep(100);
	else
		msleep(5);

	return 0;
}