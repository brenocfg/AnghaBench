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
struct dvb_frontend {struct dib9000_state* demodulator_priv; } ;
struct dib9000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUT_MSG_ENABLE_DIVERSITY ; 
 int dib9000_mbx_send (struct dib9000_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int dib9000_fw_set_diversity_in(struct dvb_frontend *fe, int onoff)
{
	struct dib9000_state *state = fe->demodulator_priv;
	u16 mode = (u16) onoff;
	return dib9000_mbx_send(state, OUT_MSG_ENABLE_DIVERSITY, &mode, 1);
}