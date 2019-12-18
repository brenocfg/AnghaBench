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
typedef  int /*<<< orphan*/  u16 ;
struct ks8842_adapter {int conf_flags; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned int ETH_ALEN ; 
 int MICREL_KS884X ; 
 scalar_t__ REG_MACAR1 ; 
 scalar_t__ REG_MACAR2 ; 
 scalar_t__ REG_MACAR3 ; 
 scalar_t__ REG_MARH ; 
 scalar_t__ REG_MARL ; 
 scalar_t__ REG_MARM ; 
 int /*<<< orphan*/  ks8842_read16 (struct ks8842_adapter*,int,scalar_t__) ; 
 int /*<<< orphan*/  ks8842_write16 (struct ks8842_adapter*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ks8842_write8 (struct ks8842_adapter*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ks8842_write_mac_addr(struct ks8842_adapter *adapter, u8 *mac)
{
	unsigned long flags;
	unsigned i;

	spin_lock_irqsave(&adapter->lock, flags);
	for (i = 0; i < ETH_ALEN; i++) {
		ks8842_write8(adapter, 2, mac[ETH_ALEN - i - 1], REG_MARL + i);
		if (!(adapter->conf_flags & MICREL_KS884X))
			ks8842_write8(adapter, 39, mac[ETH_ALEN - i - 1],
				REG_MACAR1 + i);
	}

	if (adapter->conf_flags & MICREL_KS884X) {
		/*
		the sequence of saving mac addr between MAC and Switch is
		different.
		*/

		u16 mac;

		mac = ks8842_read16(adapter, 2, REG_MARL);
		ks8842_write16(adapter, 39, mac, REG_MACAR3);
		mac = ks8842_read16(adapter, 2, REG_MARM);
		ks8842_write16(adapter, 39, mac, REG_MACAR2);
		mac = ks8842_read16(adapter, 2, REG_MARH);
		ks8842_write16(adapter, 39, mac, REG_MACAR1);
	}
	spin_unlock_irqrestore(&adapter->lock, flags);
}