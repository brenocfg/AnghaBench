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
 int /*<<< orphan*/  SDLA_WINDOW (struct net_device*,int) ; 
 int SDLA_WINDOW_SIZE ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sdla_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sdla_clear(struct net_device *dev)
{
	unsigned long flags;
	char          *base;
	int           len, addr, bytes;

	len = 65536;	
	addr = 0;
	bytes = SDLA_WINDOW_SIZE;
	base = (void *) dev->mem_start;

	spin_lock_irqsave(&sdla_lock, flags);
	while(len)
	{
		SDLA_WINDOW(dev, addr);
		memset(base, 0, bytes);

		addr += bytes;
		len  -= bytes;
	}
	spin_unlock_irqrestore(&sdla_lock, flags);

}