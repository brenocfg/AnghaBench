#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* outlvl_cache; int /*<<< orphan*/  lock; TYPE_1__* desc; int /*<<< orphan*/  gpio_base; } ;
struct TYPE_3__ {scalar_t__ use_outlvl_cache; int /*<<< orphan*/ ** regs; } ;

/* Variables and functions */
 int BIT (int) ; 
 int GPIO_LVL ; 
 int ICHX_READ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ichx_priv ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ichx_read_bit(int reg, unsigned nr)
{
	unsigned long flags;
	u32 data;
	int reg_nr = nr / 32;
	int bit = nr & 0x1f;

	spin_lock_irqsave(&ichx_priv.lock, flags);

	data = ICHX_READ(ichx_priv.desc->regs[reg][reg_nr],
			 ichx_priv.gpio_base);

	if (reg == GPIO_LVL && ichx_priv.desc->use_outlvl_cache)
		data = ichx_priv.outlvl_cache[reg_nr] | data;

	spin_unlock_irqrestore(&ichx_priv.lock, flags);

	return !!(data & BIT(bit));
}