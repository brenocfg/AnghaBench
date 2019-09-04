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
typedef  scalar_t__ u32 ;
struct ipuv3_channel {unsigned int num; struct ipu_soc* ipu; } ;
struct ipu_soc {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPU_CHA_BUF0_RDY (unsigned int) ; 
 int /*<<< orphan*/  IPU_CHA_BUF1_RDY (unsigned int) ; 
 int /*<<< orphan*/  idma_mask (unsigned int) ; 
 int /*<<< orphan*/  ipu_cm_write (struct ipu_soc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ipu_idmac_select_buffer(struct ipuv3_channel *channel, u32 buf_num)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned int chno = channel->num;
	unsigned long flags;

	spin_lock_irqsave(&ipu->lock, flags);

	/* Mark buffer as ready. */
	if (buf_num == 0)
		ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_BUF0_RDY(chno));
	else
		ipu_cm_write(ipu, idma_mask(chno), IPU_CHA_BUF1_RDY(chno));

	spin_unlock_irqrestore(&ipu->lock, flags);
}