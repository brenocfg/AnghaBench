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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {struct dib0090_state* tuner_priv; } ;
struct dib0090_state {int /*<<< orphan*/  wbd_offset; } ;

/* Variables and functions */

u16 dib0090_get_wbd_offset(struct dvb_frontend *fe)
{
	struct dib0090_state *state = fe->tuner_priv;
	return state->wbd_offset;
}