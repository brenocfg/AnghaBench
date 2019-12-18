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
struct net_device {scalar_t__ mem_start; } ;

/* Variables and functions */
 int SDLA_ADDR_MASK ; 
 int /*<<< orphan*/  SDLA_WINDOW (struct net_device*,int) ; 
 int /*<<< orphan*/  sdla_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static char sdla_byte(struct net_device *dev, int addr)
{
	unsigned long flags;
	char          byte, *temp;

	temp = (void *) (dev->mem_start + (addr & SDLA_ADDR_MASK));

	spin_lock_irqsave(&sdla_lock, flags);
	SDLA_WINDOW(dev, addr);
	byte = *temp;
	spin_unlock_irqrestore(&sdla_lock, flags);

	return byte;
}