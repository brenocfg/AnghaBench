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
typedef  scalar_t__ u32 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int lg216x_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
#if 0
	struct lg216x_state *state = fe->demodulator_priv;
	int ret;

	ret = lg216x_read_rs_err_count(state,
				       &fe->dtv_property_cache.atscmh_rs_err);
	if (lg_fail(ret))
		goto fail;

	*ucblocks = fe->dtv_property_cache.atscmh_rs_err;
fail:
#else
	*ucblocks = 0;
#endif
	return 0;
}