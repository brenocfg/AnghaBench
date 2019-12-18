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
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int BT431_CMD_4_1_MUX ; 
 int BT431_CMD_CURS_ENABLE ; 
 int BT431_CMD_OR_CURSORS ; 
 int BT431_CMD_THICK_1 ; 
 int /*<<< orphan*/  BT431_REG_CMD ; 
 int /*<<< orphan*/  bt431_write_reg (struct bt431_regs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bt431_enable_cursor(struct bt431_regs *regs)
{
	bt431_write_reg(regs, BT431_REG_CMD,
			BT431_CMD_CURS_ENABLE | BT431_CMD_OR_CURSORS
			| BT431_CMD_4_1_MUX | BT431_CMD_THICK_1);
}