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
typedef  int u32 ;
struct realtek_smi {int cmd_read; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  realtek_smi_read_byte0 (struct realtek_smi*,scalar_t__*) ; 
 int /*<<< orphan*/  realtek_smi_read_byte1 (struct realtek_smi*,scalar_t__*) ; 
 int /*<<< orphan*/  realtek_smi_start (struct realtek_smi*) ; 
 int /*<<< orphan*/  realtek_smi_stop (struct realtek_smi*) ; 
 int realtek_smi_write_byte (struct realtek_smi*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int realtek_smi_read_reg(struct realtek_smi *smi, u32 addr, u32 *data)
{
	unsigned long flags;
	u8 lo = 0;
	u8 hi = 0;
	int ret;

	spin_lock_irqsave(&smi->lock, flags);

	realtek_smi_start(smi);

	/* Send READ command */
	ret = realtek_smi_write_byte(smi, smi->cmd_read);
	if (ret)
		goto out;

	/* Set ADDR[7:0] */
	ret = realtek_smi_write_byte(smi, addr & 0xff);
	if (ret)
		goto out;

	/* Set ADDR[15:8] */
	ret = realtek_smi_write_byte(smi, addr >> 8);
	if (ret)
		goto out;

	/* Read DATA[7:0] */
	realtek_smi_read_byte0(smi, &lo);
	/* Read DATA[15:8] */
	realtek_smi_read_byte1(smi, &hi);

	*data = ((u32)lo) | (((u32)hi) << 8);

	ret = 0;

 out:
	realtek_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	return ret;
}