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
struct tc3589x {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tc3589x_reg_read (struct tc3589x*,int) ; 
 int tc3589x_reg_write (struct tc3589x*,int,int) ; 

int tc3589x_set_bits(struct tc3589x *tc3589x, u8 reg, u8 mask, u8 val)
{
	int ret;

	mutex_lock(&tc3589x->lock);

	ret = tc3589x_reg_read(tc3589x, reg);
	if (ret < 0)
		goto out;

	ret &= ~mask;
	ret |= val;

	ret = tc3589x_reg_write(tc3589x, reg, ret);

out:
	mutex_unlock(&tc3589x->lock);
	return ret;
}