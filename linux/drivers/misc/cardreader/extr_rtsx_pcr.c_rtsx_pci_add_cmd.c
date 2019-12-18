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
typedef  int u32 ;
typedef  int u16 ;
struct rtsx_pcr {int ci; int /*<<< orphan*/  lock; scalar_t__ host_cmds_ptr; } ;

/* Variables and functions */
 int HOST_CMDS_BUF_LEN ; 
 int /*<<< orphan*/  put_unaligned_le32 (int,int*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void rtsx_pci_add_cmd(struct rtsx_pcr *pcr,
		u8 cmd_type, u16 reg_addr, u8 mask, u8 data)
{
	unsigned long flags;
	u32 val = 0;
	u32 *ptr = (u32 *)(pcr->host_cmds_ptr);

	val |= (u32)(cmd_type & 0x03) << 30;
	val |= (u32)(reg_addr & 0x3FFF) << 16;
	val |= (u32)mask << 8;
	val |= (u32)data;

	spin_lock_irqsave(&pcr->lock, flags);
	ptr += pcr->ci;
	if (pcr->ci < (HOST_CMDS_BUF_LEN / 4)) {
		put_unaligned_le32(val, ptr);
		ptr++;
		pcr->ci++;
	}
	spin_unlock_irqrestore(&pcr->lock, flags);
}