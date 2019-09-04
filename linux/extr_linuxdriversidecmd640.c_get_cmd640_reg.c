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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __get_cmd640_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd640_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u8 get_cmd640_reg(u16 reg)
{
	unsigned long flags;
	u8 b;

	spin_lock_irqsave(&cmd640_lock, flags);
	b = __get_cmd640_reg(reg);
	spin_unlock_irqrestore(&cmd640_lock, flags);
	return b;
}