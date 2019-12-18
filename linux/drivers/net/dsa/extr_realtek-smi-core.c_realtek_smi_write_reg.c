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
typedef  int u32 ;
struct realtek_smi {int cmd_write; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  realtek_smi_start (struct realtek_smi*) ; 
 int /*<<< orphan*/  realtek_smi_stop (struct realtek_smi*) ; 
 int realtek_smi_write_byte (struct realtek_smi*,int) ; 
 int realtek_smi_write_byte_noack (struct realtek_smi*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int realtek_smi_write_reg(struct realtek_smi *smi,
				 u32 addr, u32 data, bool ack)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&smi->lock, flags);

	realtek_smi_start(smi);

	/* Send WRITE command */
	ret = realtek_smi_write_byte(smi, smi->cmd_write);
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

	/* Write DATA[7:0] */
	ret = realtek_smi_write_byte(smi, data & 0xff);
	if (ret)
		goto out;

	/* Write DATA[15:8] */
	if (ack)
		ret = realtek_smi_write_byte(smi, data >> 8);
	else
		ret = realtek_smi_write_byte_noack(smi, data >> 8);
	if (ret)
		goto out;

	ret = 0;

 out:
	realtek_smi_stop(smi);
	spin_unlock_irqrestore(&smi->lock, flags);

	return ret;
}