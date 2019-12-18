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
typedef  int u32 ;
typedef  int u16 ;
struct nic {int /*<<< orphan*/  netdev; int /*<<< orphan*/  mdio_lock; TYPE_1__* csr; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdi_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  hw ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int mdi_read ; 
 int mdi_ready ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u16 mdio_ctrl_hw(struct nic *nic, u32 addr, u32 dir, u32 reg, u16 data)
{
	u32 data_out = 0;
	unsigned int i;
	unsigned long flags;


	/*
	 * Stratus87247: we shouldn't be writing the MDI control
	 * register until the Ready bit shows True.  Also, since
	 * manipulation of the MDI control registers is a multi-step
	 * procedure it should be done under lock.
	 */
	spin_lock_irqsave(&nic->mdio_lock, flags);
	for (i = 100; i; --i) {
		if (ioread32(&nic->csr->mdi_ctrl) & mdi_ready)
			break;
		udelay(20);
	}
	if (unlikely(!i)) {
		netdev_err(nic->netdev, "e100.mdio_ctrl won't go Ready\n");
		spin_unlock_irqrestore(&nic->mdio_lock, flags);
		return 0;		/* No way to indicate timeout error */
	}
	iowrite32((reg << 16) | (addr << 21) | dir | data, &nic->csr->mdi_ctrl);

	for (i = 0; i < 100; i++) {
		udelay(20);
		if ((data_out = ioread32(&nic->csr->mdi_ctrl)) & mdi_ready)
			break;
	}
	spin_unlock_irqrestore(&nic->mdio_lock, flags);
	netif_printk(nic, hw, KERN_DEBUG, nic->netdev,
		     "%s:addr=%d, reg=%d, data_in=0x%04X, data_out=0x%04X\n",
		     dir == mdi_read ? "READ" : "WRITE",
		     addr, reg, data, data_out);
	return (u16)data_out;
}