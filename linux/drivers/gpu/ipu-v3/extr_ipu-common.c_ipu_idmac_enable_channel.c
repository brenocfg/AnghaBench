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
typedef  int /*<<< orphan*/  u32 ;
struct ipuv3_channel {int /*<<< orphan*/  num; struct ipu_soc* ipu; } ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDMAC_CHA_EN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idma_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_idmac_enable_channel(struct ipuv3_channel *channel)
{
	struct ipu_soc *ipu = channel->ipu;
	u32 val;
	unsigned long flags;

	spin_lock_irqsave(&ipu->lock, flags);

	val = ipu_idmac_read(ipu, IDMAC_CHA_EN(channel->num));
	val |= idma_mask(channel->num);
	ipu_idmac_write(ipu, val, IDMAC_CHA_EN(channel->num));

	spin_unlock_irqrestore(&ipu->lock, flags);

	return 0;
}