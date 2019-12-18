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
typedef  int u32 ;
struct stv090x_state {int dummy; } ;
struct dvb_frontend {struct stv090x_state* demodulator_priv; } ;
typedef  int s32 ;
typedef  enum fe_status { ____Placeholder_fe_status } fe_status ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCNT20 ; 
 int /*<<< orphan*/  ERRCNT21 ; 
 int /*<<< orphan*/  ERRCNT22 ; 
 int /*<<< orphan*/  ERRCTRL2 ; 
 int /*<<< orphan*/  ERR_CNT20_FIELD ; 
 int /*<<< orphan*/  ERR_CNT21_FIELD ; 
 int /*<<< orphan*/  ERR_CNT2_FIELD ; 
 int /*<<< orphan*/  FBERCPT0 ; 
 int /*<<< orphan*/  FBERCPT1 ; 
 int /*<<< orphan*/  FBERCPT2 ; 
 int /*<<< orphan*/  FBERCPT3 ; 
 int /*<<< orphan*/  FBERCPT4 ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int FE_HAS_LOCK ; 
 int STV090x_GETFIELD_Px (int,int /*<<< orphan*/ ) ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  stv090x_read_status (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int stv090x_read_per(struct dvb_frontend *fe, u32 *per)
{
	struct stv090x_state *state = fe->demodulator_priv;

	s32 count_4, count_3, count_2, count_1, count_0, count;
	u32 reg, h, m, l;
	enum fe_status status;

	stv090x_read_status(fe, &status);
	if (!(status & FE_HAS_LOCK)) {
		*per = 1 << 23; /* Max PER */
	} else {
		/* Counter 2 */
		reg = STV090x_READ_DEMOD(state, ERRCNT22);
		h = STV090x_GETFIELD_Px(reg, ERR_CNT2_FIELD);

		reg = STV090x_READ_DEMOD(state, ERRCNT21);
		m = STV090x_GETFIELD_Px(reg, ERR_CNT21_FIELD);

		reg = STV090x_READ_DEMOD(state, ERRCNT20);
		l = STV090x_GETFIELD_Px(reg, ERR_CNT20_FIELD);

		*per = ((h << 16) | (m << 8) | l);

		count_4 = STV090x_READ_DEMOD(state, FBERCPT4);
		count_3 = STV090x_READ_DEMOD(state, FBERCPT3);
		count_2 = STV090x_READ_DEMOD(state, FBERCPT2);
		count_1 = STV090x_READ_DEMOD(state, FBERCPT1);
		count_0 = STV090x_READ_DEMOD(state, FBERCPT0);

		if ((!count_4) && (!count_3)) {
			count  = (count_2 & 0xff) << 16;
			count |= (count_1 & 0xff) <<  8;
			count |=  count_0 & 0xff;
		} else {
			count = 1 << 24;
		}
		if (count == 0)
			*per = 1;
	}
	if (STV090x_WRITE_DEMOD(state, FBERCPT4, 0) < 0)
		goto err;
	if (STV090x_WRITE_DEMOD(state, ERRCTRL2, 0xc1) < 0)
		goto err;

	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}