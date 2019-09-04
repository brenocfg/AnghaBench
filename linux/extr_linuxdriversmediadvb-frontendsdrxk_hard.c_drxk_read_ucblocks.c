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
typedef  scalar_t__ u16 ;
struct dvb_frontend {struct drxk_state* demodulator_priv; } ;
struct drxk_state {scalar_t__ m_drxk_state; } ;

/* Variables and functions */
 scalar_t__ DRXK_NO_DEV ; 
 scalar_t__ DRXK_UNINITIALIZED ; 
 int EAGAIN ; 
 int ENODEV ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  dvbtqam_get_acc_pkt_err (struct drxk_state*,scalar_t__*) ; 

__attribute__((used)) static int drxk_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct drxk_state *state = fe->demodulator_priv;
	u16 err;

	dprintk(1, "\n");

	if (state->m_drxk_state == DRXK_NO_DEV)
		return -ENODEV;
	if (state->m_drxk_state == DRXK_UNINITIALIZED)
		return -EAGAIN;

	dvbtqam_get_acc_pkt_err(state, &err);
	*ucblocks = (u32) err;
	return 0;
}