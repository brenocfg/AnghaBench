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
struct ipuv3_channel {unsigned int num; struct ipu_soc* ipu; } ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY (unsigned int) ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY (unsigned int) ; 
 int /*<<< orphan*/  IPU_CHA_BUF2_RDY (unsigned int) ; 
 int /*<<< orphan*/  IPU_GPR ; 
 int idma_mask (unsigned int) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_idmac_clear_buffer(struct ipuv3_channel *channel, u32 buf_num)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned int chno = channel->num;
	unsigned long flags;

	spin_lock_irqsave(&ipu->lock, flags);

	ipu_cm_write(ipu, 0xF0300000, IPU_GPR); /* write one to clear */
	switch (buf_num) {
	case 0:
		ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_BUF0_RDY(chno));
		break;
	case 1:
		ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_BUF1_RDY(chno));
		break;
	case 2:
		ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_BUF2_RDY(chno));
		break;
	default:
		break;
	}
	ipu_cm_write(ipu, 0x0, IPU_GPR); /* write one to set */

	spin_unlock_irqrestore(&ipu->lock, flags);
}