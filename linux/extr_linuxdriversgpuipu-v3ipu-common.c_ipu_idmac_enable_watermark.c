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
struct ipuv3_channel {int num; struct ipu_soc* ipu; } ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_WM_EN (int) ; 
 int ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_write (struct ipu_soc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_idmac_enable_watermark(struct ipuv3_channel *channel, bool enable)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned long flags;
	u32 val;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_idmac_read(ipu, IDMAC_WM_EN(channel->num));
	if (enable)
		val |= 1 << (channel->num % 32);
	else
		val &= ~(1 << (channel->num % 32));
	ipu_idmac_write(ipu, val, IDMAC_WM_EN(channel->num));

	spin_unlock_irqrestore(&ipu->lock, flags);
}