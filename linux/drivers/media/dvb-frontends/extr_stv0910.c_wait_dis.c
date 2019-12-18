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
struct stv {scalar_t__ nr; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int RSTV0910_P1_DISTXSTATUS ; 
 int /*<<< orphan*/  read_reg (struct stv*,int,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wait_dis(struct stv *state, u8 flag, u8 val)
{
	int i;
	u8 stat;
	u16 offs = state->nr ? 0x40 : 0;

	for (i = 0; i < 10; i++) {
		read_reg(state, RSTV0910_P1_DISTXSTATUS + offs, &stat);
		if ((stat & flag) == val)
			return 0;
		usleep_range(10000, 11000);
	}
	return -ETIMEDOUT;
}