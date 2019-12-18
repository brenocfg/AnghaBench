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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct btc_coexist {int dummy; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_OP_WRITE_REG_ADDR ; 
 int /*<<< orphan*/  BT_OP_WRITE_REG_VALUE ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  halbtc_send_bt_mp_operation (struct btc_coexist*,int /*<<< orphan*/ ,scalar_t__*,int,int) ; 

__attribute__((used)) static
void halbtc_set_bt_reg(void *btc_context, u8 reg_type, u32 offset, u32 set_val)
{
	struct btc_coexist *btcoexist = (struct btc_coexist *)btc_context;
	u8 cmd_buffer1[4] = {0};
	u8 cmd_buffer2[4] = {0};

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	*((__le16 *)&cmd_buffer1[2]) = cpu_to_le16((u16)set_val);
	if (!halbtc_send_bt_mp_operation(btcoexist, BT_OP_WRITE_REG_VALUE,
					 cmd_buffer1, 4, 200))
		return;

	/* cmd_buffer[0] and [1] is filled by halbtc_send_bt_mp_operation() */
	cmd_buffer2[2] = reg_type;
	*((u8 *)&cmd_buffer2[3]) = (u8)offset;
	halbtc_send_bt_mp_operation(btcoexist, BT_OP_WRITE_REG_ADDR,
				    cmd_buffer2, 4, 200);
}