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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DMDSTATE ; 
 int /*<<< orphan*/  DSTATUS ; 
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  HEADER_MODE_FIELD ; 
 int /*<<< orphan*/  LOCK_DEFINITIF_FIELD ; 
 void* STV090x_GETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int stv090x_get_dmdlock(struct stv090x_state *state, s32 timeout)
{
	s32 timer = 0, lock = 0;
	u32 reg;
	u8 stat;

	while ((timer < timeout) && (!lock)) {
		reg = STV090x_READ_DEMOD(state, DMDSTATE);
		stat = STV090x_GETFIELD_Px(reg, HEADER_MODE_FIELD);

		switch (stat) {
		case 0: /* searching */
		case 1: /* first PLH detected */
		default:
			dprintk(FE_DEBUG, 1, "Demodulator searching ..");
			lock = 0;
			break;
		case 2: /* DVB-S2 mode */
		case 3: /* DVB-S1/legacy mode */
			reg = STV090x_READ_DEMOD(state, DSTATUS);
			lock = STV090x_GETFIELD_Px(reg, LOCK_DEFINITIF_FIELD);
			break;
		}

		if (!lock)
			msleep(10);
		else
			dprintk(FE_DEBUG, 1, "Demodulator acquired LOCK");

		timer += 10;
	}
	return lock;
}