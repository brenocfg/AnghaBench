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
struct sca3000_state {int* rx; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int SCA3000_MD_CTRL_PROT_MASK ; 
 int SCA3000_MODE_PROT_MASK ; 
 int /*<<< orphan*/  SCA3000_REG_CTRL_SEL_MD_CTRL ; 
 int /*<<< orphan*/  SCA3000_REG_CTRL_SEL_OUT_CTRL ; 
 int SCA3000_REG_INT_MASK_ACTIVE_LOW ; 
 int /*<<< orphan*/  SCA3000_REG_INT_MASK_ADDR ; 
 int SCA3000_REG_INT_MASK_PROT_MASK ; 
 int /*<<< orphan*/  SCA3000_REG_INT_STATUS_ADDR ; 
 int /*<<< orphan*/  SCA3000_REG_MODE_ADDR ; 
 int SCA3000_REG_OUT_CTRL_BUF_DIV_4 ; 
 int SCA3000_REG_OUT_CTRL_BUF_X_EN ; 
 int SCA3000_REG_OUT_CTRL_BUF_Y_EN ; 
 int SCA3000_REG_OUT_CTRL_BUF_Z_EN ; 
 int SCA3000_REG_OUT_CTRL_PROT_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_ctrl_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_clean_setup(struct sca3000_state *st)
{
	int ret;

	mutex_lock(&st->lock);
	/* Ensure all interrupts have been acknowledged */
	ret = sca3000_read_data_short(st, SCA3000_REG_INT_STATUS_ADDR, 1);
	if (ret)
		goto error_ret;

	/* Turn off all motion detection channels */
	ret = sca3000_read_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL);
	if (ret < 0)
		goto error_ret;
	ret = sca3000_write_ctrl_reg(st, SCA3000_REG_CTRL_SEL_MD_CTRL,
				     ret & SCA3000_MD_CTRL_PROT_MASK);
	if (ret)
		goto error_ret;

	/* Disable ring buffer */
	ret = sca3000_read_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL);
	if (ret < 0)
		goto error_ret;
	ret = sca3000_write_ctrl_reg(st, SCA3000_REG_CTRL_SEL_OUT_CTRL,
				     (ret & SCA3000_REG_OUT_CTRL_PROT_MASK)
				     | SCA3000_REG_OUT_CTRL_BUF_X_EN
				     | SCA3000_REG_OUT_CTRL_BUF_Y_EN
				     | SCA3000_REG_OUT_CTRL_BUF_Z_EN
				     | SCA3000_REG_OUT_CTRL_BUF_DIV_4);
	if (ret)
		goto error_ret;
	/* Enable interrupts, relevant to mode and set up as active low */
	ret = sca3000_read_data_short(st, SCA3000_REG_INT_MASK_ADDR, 1);
	if (ret)
		goto error_ret;
	ret = sca3000_write_reg(st,
				SCA3000_REG_INT_MASK_ADDR,
				(ret & SCA3000_REG_INT_MASK_PROT_MASK)
				| SCA3000_REG_INT_MASK_ACTIVE_LOW);
	if (ret)
		goto error_ret;
	/*
	 * Select normal measurement mode, free fall off, ring off
	 * Ring in 12 bit mode - it is fine to overwrite reserved bits 3,5
	 * as that occurs in one of the example on the datasheet
	 */
	ret = sca3000_read_data_short(st, SCA3000_REG_MODE_ADDR, 1);
	if (ret)
		goto error_ret;
	ret = sca3000_write_reg(st, SCA3000_REG_MODE_ADDR,
				(st->rx[0] & SCA3000_MODE_PROT_MASK));

error_ret:
	mutex_unlock(&st->lock);
	return ret;
}