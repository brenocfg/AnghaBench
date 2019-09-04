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
struct file {int dummy; } ;
struct dt3155_priv {unsigned int input; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_ADDR ; 
 int /*<<< orphan*/  AD_CMD ; 
 unsigned int AD_CMD_REG ; 
 int EINVAL ; 
 unsigned int SYNC_LVL_3 ; 
 struct dt3155_priv* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  write_i2c_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int dt3155_s_input(struct file *filp, void *p, unsigned int i)
{
	struct dt3155_priv *pd = video_drvdata(filp);

	if (i > 3)
		return -EINVAL;
	pd->input = i;
	write_i2c_reg(pd->regs, AD_ADDR, AD_CMD_REG);
	write_i2c_reg(pd->regs, AD_CMD, (i << 6) | (i << 4) | SYNC_LVL_3);
	return 0;
}