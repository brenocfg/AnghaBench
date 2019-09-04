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
struct dvb_frontend {struct dib3000_state* demodulator_priv; } ;
struct dib3000_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIB3000MB_REG_PID_PARSE ; 
 int /*<<< orphan*/  deb_xfer (char*,char*) ; 
 int /*<<< orphan*/  wr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dib3000mb_pid_parse(struct dvb_frontend *fe, int onoff)
{
	struct dib3000_state *state = fe->demodulator_priv;
	deb_xfer("%s pid parsing\n",onoff ? "enabling" : "disabling");
	wr(DIB3000MB_REG_PID_PARSE,onoff);
	return 0;
}