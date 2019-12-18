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
typedef  int u16 ;
struct lgs8gl5_state {int dummy; } ;
struct dvb_frontend {struct lgs8gl5_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_STRENGTH ; 
 int REG_STRENGTH_MASK ; 
 int lgs8gl5_read_reg (struct lgs8gl5_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lgs8gl5_read_snr(struct dvb_frontend *fe, u16 *snr)
{
	struct lgs8gl5_state *state = fe->demodulator_priv;
	u8 level = lgs8gl5_read_reg(state, REG_STRENGTH);
	*snr = (level & REG_STRENGTH_MASK) << 8;

	return 0;
}