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
struct lgdt3306a_state {int dummy; } ;
struct dvb_frontend {struct lgdt3306a_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_info (char*,int) ; 
 int lgdt3306a_mpeg_tristate (struct lgdt3306a_state*,int) ; 

__attribute__((used)) static int lgdt3306a_ts_bus_ctrl(struct dvb_frontend *fe, int acquire)
{
	struct lgdt3306a_state *state = fe->demodulator_priv;

	dbg_info("acquire=%d\n", acquire);

	return lgdt3306a_mpeg_tristate(state, acquire ? 0 : 1);

}