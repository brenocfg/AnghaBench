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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct w5100_mmio_priv {int /*<<< orphan*/  reg_lock; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  W5100_IDM_AR ; 
 int /*<<< orphan*/  W5100_IDM_DR ; 
 int /*<<< orphan*/  __w5100_write_direct (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct w5100_mmio_priv* w5100_mmio_priv (struct net_device*) ; 
 int /*<<< orphan*/  w5100_write16_direct (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w5100_writebulk_indirect(struct net_device *ndev, u32 addr,
				    const u8 *buf, int len)
{
	struct w5100_mmio_priv *mmio_priv = w5100_mmio_priv(ndev);
	unsigned long flags;
	int i;

	spin_lock_irqsave(&mmio_priv->reg_lock, flags);
	w5100_write16_direct(ndev, W5100_IDM_AR, addr);

	for (i = 0; i < len; i++)
		__w5100_write_direct(ndev, W5100_IDM_DR, *buf++);

	spin_unlock_irqrestore(&mmio_priv->reg_lock, flags);

	return 0;
}