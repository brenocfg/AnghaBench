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
struct mtu3 {int /*<<< orphan*/  lock; int /*<<< orphan*/  mac_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BMU_INTR ; 
 int EP_CTRL_INTR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int MAC2_INTR ; 
 int MAC3_INTR ; 
 int QMU_INTR ; 
 int /*<<< orphan*/  U3D_LV1IER ; 
 int /*<<< orphan*/  U3D_LV1ISR ; 
 int /*<<< orphan*/  mtu3_ep0_isr (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_link_isr (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_qmu_isr (struct mtu3*) ; 
 int mtu3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtu3_u2_common_isr (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_u3_ltssm_isr (struct mtu3*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t mtu3_irq(int irq, void *data)
{
	struct mtu3 *mtu = (struct mtu3 *)data;
	unsigned long flags;
	u32 level1;

	spin_lock_irqsave(&mtu->lock, flags);

	/* U3D_LV1ISR is RU */
	level1 = mtu3_readl(mtu->mac_base, U3D_LV1ISR);
	level1 &= mtu3_readl(mtu->mac_base, U3D_LV1IER);

	if (level1 & EP_CTRL_INTR)
		mtu3_link_isr(mtu);

	if (level1 & MAC2_INTR)
		mtu3_u2_common_isr(mtu);

	if (level1 & MAC3_INTR)
		mtu3_u3_ltssm_isr(mtu);

	if (level1 & BMU_INTR)
		mtu3_ep0_isr(mtu);

	if (level1 & QMU_INTR)
		mtu3_qmu_isr(mtu);

	spin_unlock_irqrestore(&mtu->lock, flags);

	return IRQ_HANDLED;
}