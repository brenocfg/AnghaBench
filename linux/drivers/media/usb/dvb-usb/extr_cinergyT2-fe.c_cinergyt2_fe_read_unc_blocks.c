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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct cinergyt2_fe_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  uncorrected_block_count; } ;
struct cinergyt2_fe_state {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cinergyt2_fe_read_unc_blocks(struct dvb_frontend *fe, u32 *unc)
{
	struct cinergyt2_fe_state *state = fe->demodulator_priv;

	*unc = le32_to_cpu(state->status.uncorrected_block_count);
	return 0;
}