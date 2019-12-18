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
struct kvaser_pciefd_can {int /*<<< orphan*/  lock; scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVASER_PCIEFD_KCAN_MODE_EPEN ; 
 scalar_t__ KVASER_PCIEFD_KCAN_MODE_REG ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void kvaser_pciefd_disable_err_gen(struct kvaser_pciefd_can *can)
{
	u32 mode;
	unsigned long irq;

	spin_lock_irqsave(&can->lock, irq);
	mode = ioread32(can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	mode &= ~KVASER_PCIEFD_KCAN_MODE_EPEN;
	iowrite32(mode, can->reg_base + KVASER_PCIEFD_KCAN_MODE_REG);
	spin_unlock_irqrestore(&can->lock, irq);
}