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
typedef  int /*<<< orphan*/  u8 ;
struct v4l2_subdev {int dummy; } ;
struct tvp514x_reg {scalar_t__ token; scalar_t__ val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ TOK_DELAY ; 
 scalar_t__ TOK_SKIP ; 
 scalar_t__ TOK_TERM ; 
 int /*<<< orphan*/  msleep (scalar_t__) ; 
 int tvp514x_write_reg (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int tvp514x_write_regs(struct v4l2_subdev *sd,
			      const struct tvp514x_reg reglist[])
{
	int err;
	const struct tvp514x_reg *next = reglist;

	for (; next->token != TOK_TERM; next++) {
		if (next->token == TOK_DELAY) {
			msleep(next->val);
			continue;
		}

		if (next->token == TOK_SKIP)
			continue;

		err = tvp514x_write_reg(sd, next->reg, (u8) next->val);
		if (err) {
			v4l2_err(sd, "Write failed. Err[%d]\n", err);
			return err;
		}
	}
	return 0;
}