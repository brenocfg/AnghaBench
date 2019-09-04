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
typedef  int /*<<< orphan*/  u32 ;
struct stv090x_state {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int STV090x_GETFIELD_Px (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSFIFO_LINEOK_FIELD ; 
 int /*<<< orphan*/  TSSTATUS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stv090x_get_dmdlock (struct stv090x_state*,scalar_t__) ; 
 int stv090x_get_feclock (struct stv090x_state*,scalar_t__) ; 

__attribute__((used)) static int stv090x_get_lock(struct stv090x_state *state, s32 timeout_dmd, s32 timeout_fec)
{
	u32 reg;
	s32 timer = 0;
	int lock;

	lock = stv090x_get_dmdlock(state, timeout_dmd);
	if (lock)
		lock = stv090x_get_feclock(state, timeout_fec);

	if (lock) {
		lock = 0;

		while ((timer < timeout_fec) && (!lock)) {
			reg = STV090x_READ_DEMOD(state, TSSTATUS);
			lock = STV090x_GETFIELD_Px(reg, TSFIFO_LINEOK_FIELD);
			msleep(1);
			timer++;
		}
	}

	return lock;
}