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
struct he_dev {int /*<<< orphan*/  global_lock; } ;
struct atm_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ FRAMER ; 
 struct he_dev* HE_DEV (struct atm_dev*) ; 
 int /*<<< orphan*/  HPRINTK (char*,unsigned long,unsigned int) ; 
 unsigned int he_readl (struct he_dev*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned char
he_phy_get(struct atm_dev *atm_dev, unsigned long addr)
{ 
	unsigned long flags;
	struct he_dev *he_dev = HE_DEV(atm_dev);
	unsigned reg;

	spin_lock_irqsave(&he_dev->global_lock, flags);
	reg = he_readl(he_dev, FRAMER + (addr*4));
	spin_unlock_irqrestore(&he_dev->global_lock, flags);

	HPRINTK("phy_get(addr 0x%lx) =0x%x\n", addr, reg);
	return reg;
}