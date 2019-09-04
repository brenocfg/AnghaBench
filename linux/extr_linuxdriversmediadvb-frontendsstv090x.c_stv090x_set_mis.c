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

/* Variables and functions */
 int /*<<< orphan*/  FE_DEBUG ; 
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  FILTER_EN_FIELD ; 
 int /*<<< orphan*/  ISIBITENA ; 
 int /*<<< orphan*/  ISIENTRY ; 
 int /*<<< orphan*/  PDELCTRL1 ; 
 int STV090x_READ_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STV090x_SETFIELD_Px (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ STV090x_WRITE_DEMOD (struct stv090x_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,...) ; 

__attribute__((used)) static int stv090x_set_mis(struct stv090x_state *state, int mis)
{
	u32 reg;

	if (mis < 0 || mis > 255) {
		dprintk(FE_DEBUG, 1, "Disable MIS filtering");
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x00);
		if (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			goto err;
	} else {
		dprintk(FE_DEBUG, 1, "Enable MIS filtering - %d", mis);
		reg = STV090x_READ_DEMOD(state, PDELCTRL1);
		STV090x_SETFIELD_Px(reg, FILTER_EN_FIELD, 0x01);
		if (STV090x_WRITE_DEMOD(state, PDELCTRL1, reg) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, ISIENTRY, mis) < 0)
			goto err;
		if (STV090x_WRITE_DEMOD(state, ISIBITENA, 0xff) < 0)
			goto err;
	}
	return 0;
err:
	dprintk(FE_ERROR, 1, "I/O error");
	return -1;
}