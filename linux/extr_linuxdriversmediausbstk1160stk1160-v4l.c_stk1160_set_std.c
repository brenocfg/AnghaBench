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
struct stk1160 {int norm; } ;
struct regval {int member_0; int member_1; int reg; int /*<<< orphan*/  val; } ;

/* Variables and functions */
#define  STK116_CFEPO 137 
#define  STK116_CFEPO_ENX_H 136 
#define  STK116_CFEPO_ENX_L 135 
#define  STK116_CFEPO_ENY_H 134 
#define  STK116_CFEPO_ENY_L 133 
#define  STK116_CFSPO 132 
#define  STK116_CFSPO_STX_H 131 
#define  STK116_CFSPO_STX_L 130 
#define  STK116_CFSPO_STY_H 129 
#define  STK116_CFSPO_STY_L 128 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  stk1160_dbg (char*) ; 
 int /*<<< orphan*/  stk1160_write_reg (struct stk1160*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stk1160_set_std(struct stk1160 *dev)
{
	int i;

	static struct regval std525[] = {

		/* 720x480 */

		/* Frame start */
		{STK116_CFSPO_STX_L, 0x0000},
		{STK116_CFSPO_STX_H, 0x0000},
		{STK116_CFSPO_STY_L, 0x0003},
		{STK116_CFSPO_STY_H, 0x0000},

		/* Frame end */
		{STK116_CFEPO_ENX_L, 0x05a0},
		{STK116_CFEPO_ENX_H, 0x0005},
		{STK116_CFEPO_ENY_L, 0x00f3},
		{STK116_CFEPO_ENY_H, 0x0000},

		{0xffff, 0xffff}
	};

	static struct regval std625[] = {

		/* 720x576 */

		/* TODO: Each line of frame has some junk at the end */
		/* Frame start */
		{STK116_CFSPO,   0x0000},
		{STK116_CFSPO+1, 0x0000},
		{STK116_CFSPO+2, 0x0001},
		{STK116_CFSPO+3, 0x0000},

		/* Frame end */
		{STK116_CFEPO,   0x05a0},
		{STK116_CFEPO+1, 0x0005},
		{STK116_CFEPO+2, 0x0121},
		{STK116_CFEPO+3, 0x0001},

		{0xffff, 0xffff}
	};

	if (dev->norm & V4L2_STD_525_60) {
		stk1160_dbg("registers to NTSC like standard\n");
		for (i = 0; std525[i].reg != 0xffff; i++)
			stk1160_write_reg(dev, std525[i].reg, std525[i].val);
	} else {
		stk1160_dbg("registers to PAL like standard\n");
		for (i = 0; std625[i].reg != 0xffff; i++)
			stk1160_write_reg(dev, std625[i].reg, std625[i].val);
	}

}