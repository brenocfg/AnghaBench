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
typedef  int u8 ;
typedef  int u32 ;
struct stv {int last_berdenominator; int berscale; int last_bernumerator; scalar_t__ regoff; int /*<<< orphan*/  fectype; scalar_t__ mod_cod; } ;
typedef  enum dvbs2_mod_cod { ____Placeholder_dvbs2_mod_cod } dvbs2_mod_cod ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ RSTV0910_P2_ERRCNT12 ; 
 scalar_t__ RSTV0910_P2_ERRCTRL1 ; 
 int dvbs2_nbch (int,int /*<<< orphan*/ ) ; 
 int read_regs (struct stv*,scalar_t__,int*,int) ; 
 int /*<<< orphan*/  write_reg (struct stv*,scalar_t__,int) ; 

__attribute__((used)) static int get_bit_error_rate_s2(struct stv *state, u32 *bernumerator,
				 u32 *berdenominator)
{
	u8 regs[3];

	int status = read_regs(state, RSTV0910_P2_ERRCNT12 + state->regoff,
			       regs, 3);

	if (status)
		return -EINVAL;

	if ((regs[0] & 0x80) == 0) {
		state->last_berdenominator =
			dvbs2_nbch((enum dvbs2_mod_cod)state->mod_cod,
				   state->fectype) <<
			(state->berscale * 2);
		state->last_bernumerator = (((u32)regs[0] & 0x7F) << 16) |
			((u32)regs[1] << 8) | regs[2];
		if (state->last_bernumerator < 256 && state->berscale < 6) {
			state->berscale += 1;
			write_reg(state, RSTV0910_P2_ERRCTRL1 + state->regoff,
				  0x20 | state->berscale);
		} else if (state->last_bernumerator > 1024 &&
			   state->berscale > 2) {
			state->berscale -= 1;
			write_reg(state, RSTV0910_P2_ERRCTRL1 + state->regoff,
				  0x20 | state->berscale);
		}
	}
	*bernumerator = state->last_bernumerator;
	*berdenominator = state->last_berdenominator;
	return status;
}