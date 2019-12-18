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
struct ipuv3_channel {int /*<<< orphan*/  num; struct ipu_soc* ipu; } ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPU_CHA_BUF2_RDY (int /*<<< orphan*/ ) ; 
 int idma_mask (int /*<<< orphan*/ ) ; 
 int ipu_cm_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool ipu_idmac_buffer_is_ready(struct ipuv3_channel *channel, u32 buf_num)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned long flags;
	u32 reg = 0;

	spin_lock_irqsave(&ipu->lock, flags);
	switch (buf_num) {
	case 0:
		reg = ipu_cm_read(ipu, IPU_CHA_BUF0_RDY(channel->num));
		break;
	case 1:
		reg = ipu_cm_read(ipu, IPU_CHA_BUF1_RDY(channel->num));
		break;
	case 2:
		reg = ipu_cm_read(ipu, IPU_CHA_BUF2_RDY(channel->num));
		break;
	}
	spin_unlock_irqrestore(&ipu->lock, flags);

	return ((reg & idma_mask(channel->num)) != 0);
}