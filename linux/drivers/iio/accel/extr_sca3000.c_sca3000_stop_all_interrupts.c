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
 int /*<<< orphan*/  SCA3000_REG_INT_MASK_ADDR ; 
 int SCA3000_REG_INT_MASK_ALL_INTS ; 
 int SCA3000_REG_INT_MASK_RING_HALF ; 
 int SCA3000_REG_INT_MASK_RING_THREE_QUARTER ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sca3000_read_data_short (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 
 int sca3000_write_reg (struct sca3000_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sca3000_stop_all_interrupts(struct sca3000_state *st)
{
	int ret;

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_INT_MASK_ADDR, 1);
	if (ret)
		goto error_ret;
	ret = sca3000_write_reg(st, SCA3000_REG_INT_MASK_ADDR,
				(st->rx[0] &
				 ~(SCA3000_REG_INT_MASK_RING_THREE_QUARTER |
				   SCA3000_REG_INT_MASK_RING_HALF |
				   SCA3000_REG_INT_MASK_ALL_INTS)));
error_ret:
	mutex_unlock(&st->lock);
	return ret;
}