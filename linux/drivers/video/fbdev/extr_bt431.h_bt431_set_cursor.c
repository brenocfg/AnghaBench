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
typedef  int u16 ;
struct bt431_regs {int dummy; } ;

/* Variables and functions */
 int BT431_CURSOR_SIZE ; 
 int /*<<< orphan*/  BT431_REG_CRAM_BASE ; 
 int DIV_ROUND_UP (int,int) ; 
 int ROP_XOR ; 
 int /*<<< orphan*/  bt431_select_reg (struct bt431_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt431_write_cmap_inc (struct bt431_regs*,int) ; 

__attribute__((used)) static inline void bt431_set_cursor(struct bt431_regs *regs,
				    const char *data, const char *mask,
				    u16 rop, u16 width, u16 height)
{
	u16 x, y;
	int i;

	i = 0;
	width = DIV_ROUND_UP(width, 8);
	bt431_select_reg(regs, BT431_REG_CRAM_BASE);
	for (y = 0; y < BT431_CURSOR_SIZE; y++)
		for (x = 0; x < BT431_CURSOR_SIZE / 8; x++) {
			u16 val = 0;

			if (y < height && x < width) {
				val = mask[i];
				if (rop == ROP_XOR)
					val = (val << 8) | (val ^ data[i]);
				else
					val = (val << 8) | (val & data[i]);
				i++;
			}
			bt431_write_cmap_inc(regs, val);
		}
}