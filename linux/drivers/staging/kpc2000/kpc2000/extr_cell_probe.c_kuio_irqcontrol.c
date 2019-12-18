#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct uio_info {struct kpc_uio_device* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_base_num; } ;
struct kpc_uio_device {TYPE_1__ cte; struct kp2000_device* pcard; } ;
struct kp2000_device {int /*<<< orphan*/  sem; scalar_t__ sysinfo_regs_base; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_ULL (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readq (scalar_t__) ; 
 int /*<<< orphan*/  writeq (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static
int kuio_irqcontrol(struct uio_info *uioinfo, s32 irq_on)
{
	struct kpc_uio_device *kudev = uioinfo->priv;
	struct kp2000_device *pcard = kudev->pcard;
	u64 mask;

	mutex_lock(&pcard->sem);
	mask = readq(pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	if (irq_on)
		mask &= ~(BIT_ULL(kudev->cte.irq_base_num));
	else
		mask |= BIT_ULL(kudev->cte.irq_base_num);
	writeq(mask, pcard->sysinfo_regs_base + REG_INTERRUPT_MASK);
	mutex_unlock(&pcard->sem);

	return 0;
}