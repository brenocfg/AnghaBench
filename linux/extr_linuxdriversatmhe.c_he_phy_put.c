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
 int /*<<< orphan*/  HPRINTK (char*,unsigned char,unsigned long) ; 
 int /*<<< orphan*/  he_readl (struct he_dev*,scalar_t__) ; 
 int /*<<< orphan*/  he_writel (struct he_dev*,unsigned char,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
he_phy_put(struct atm_dev *atm_dev, unsigned char val, unsigned long addr)
{
	unsigned long flags;
	struct he_dev *he_dev = HE_DEV(atm_dev);

	HPRINTK("phy_put(val 0x%x, addr 0x%lx)\n", val, addr);

	spin_lock_irqsave(&he_dev->global_lock, flags);
	he_writel(he_dev, val, FRAMER + (addr*4));
	(void) he_readl(he_dev, FRAMER + (addr*4));		/* flush posted writes */
	spin_unlock_irqrestore(&he_dev->global_lock, flags);
}