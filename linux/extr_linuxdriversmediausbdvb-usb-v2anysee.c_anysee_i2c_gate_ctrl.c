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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_IOE ; 
 int anysee_wr_reg_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fe_to_d (struct dvb_frontend*) ; 

__attribute__((used)) static int anysee_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	/* enable / disable tuner access on IOE[4] */
	return anysee_wr_reg_mask(fe_to_d(fe), REG_IOE, (enable << 4), 0x10);
}