#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct rtsx_chip {int ci; TYPE_1__* rtsx; scalar_t__ host_cmds_ptr; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int HOST_CMDS_BUF_LEN ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void rtsx_add_cmd(struct rtsx_chip *chip,
		  u8 cmd_type, u16 reg_addr, u8 mask, u8 data)
{
	__le32 *cb = (__le32 *)(chip->host_cmds_ptr);
	u32 val = 0;

	val |= (u32)(cmd_type & 0x03) << 30;
	val |= (u32)(reg_addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	spin_lock_irq(&chip->rtsx->reg_lock);
	if (chip->ci < (HOST_CMDS_BUF_LEN / 4))
		cb[(chip->ci)++] = cpu_to_le32(val);

	spin_unlock_irq(&chip->rtsx->reg_lock);
}