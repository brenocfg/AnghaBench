#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct ipuv3_channel {scalar_t__ num; struct ipu_soc* ipu; } ;
struct ipu_soc {scalar_t__ ipu_type; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {scalar_t__ chnum; int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 scalar_t__ IPUV3H ; 
 TYPE_1__* idmac_lock_en_info ; 
 int ipu_idmac_read (struct ipu_soc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_idmac_write (struct ipu_soc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ipu_idmac_lock_enable(struct ipuv3_channel *channel, int num_bursts)
{
	struct ipu_soc *ipu = channel->ipu;
	unsigned long flags;
	u32 bursts, regval;
	int i;

	switch (num_bursts) {
	case 0:
	case 1:
		bursts = 0x00; /* locking disabled */
		break;
	case 2:
		bursts = 0x01;
		break;
	case 4:
		bursts = 0x02;
		break;
	case 8:
		bursts = 0x03;
		break;
	default:
		return -EINVAL;
	}

	/*
	 * IPUv3EX / i.MX51 has a different register layout, and on IPUv3M /
	 * i.MX53 channel arbitration locking doesn't seem to work properly.
	 * Allow enabling the lock feature on IPUv3H / i.MX6 only.
	 */
	if (bursts && ipu->ipu_type != IPUV3H)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(idmac_lock_en_info); i++) {
		if (channel->num == idmac_lock_en_info[i].chnum)
			break;
	}
	if (i >= ARRAY_SIZE(idmac_lock_en_info))
		return -EINVAL;

	spin_lock_irqsave(&ipu->lock, flags);

	regval = ipu_idmac_read(ipu, idmac_lock_en_info[i].reg);
	regval &= ~(0x03 << idmac_lock_en_info[i].shift);
	regval |= (bursts << idmac_lock_en_info[i].shift);
	ipu_idmac_write(ipu, regval, idmac_lock_en_info[i].reg);

	spin_unlock_irqrestore(&ipu->lock, flags);

	return 0;
}