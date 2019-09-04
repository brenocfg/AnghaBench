#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  device_name; } ;
typedef  TYPE_1__ MGSLPC_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIT6 ; 
 scalar_t__ CHA ; 
 scalar_t__ DAFO ; 
 scalar_t__ DEBUG_LEVEL_INFO ; 
 int EINVAL ; 
 int /*<<< orphan*/  clear_reg_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ debug_level ; 
 scalar_t__ mgslpc_paranoia_check (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_reg_bits (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mgslpc_break(struct tty_struct *tty, int break_state)
{
	MGSLPC_INFO * info = (MGSLPC_INFO *)tty->driver_data;
	unsigned long flags;

	if (debug_level >= DEBUG_LEVEL_INFO)
		printk("%s(%d):mgslpc_break(%s,%d)\n",
			 __FILE__, __LINE__, info->device_name, break_state);

	if (mgslpc_paranoia_check(info, tty->name, "mgslpc_break"))
		return -EINVAL;

	spin_lock_irqsave(&info->lock, flags);
	if (break_state == -1)
		set_reg_bits(info, CHA+DAFO, BIT6);
	else
		clear_reg_bits(info, CHA+DAFO, BIT6);
	spin_unlock_irqrestore(&info->lock, flags);
	return 0;
}