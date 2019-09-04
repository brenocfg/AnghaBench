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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_TUNER ; 
 int /*<<< orphan*/  DIB3000_TUNER_WRITE_DISABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIB3000_TUNER_WRITE_ENABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dib3000mb_tuner_pass_ctrl(struct dvb_frontend *fe, int onoff, u8 pll_addr)
{
	struct dib3000_state *state = fe->demodulator_priv;
	if (onoff) {
		wr(DIB3000MB_REG_TUNER, DIB3000_TUNER_WRITE_ENABLE(pll_addr));
	} else {
		wr(DIB3000MB_REG_TUNER, DIB3000_TUNER_WRITE_DISABLE(pll_addr));
	}
	return 0;
}