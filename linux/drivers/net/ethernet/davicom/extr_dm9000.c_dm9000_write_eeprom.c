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
typedef  int u8 ;
struct board_info {int flags; int /*<<< orphan*/  addr_lock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DM9000_EPAR ; 
 int /*<<< orphan*/  DM9000_EPCR ; 
 int /*<<< orphan*/  DM9000_EPDRH ; 
 int /*<<< orphan*/  DM9000_EPDRL ; 
 int DM9000_PLATF_NO_EEPROM ; 
 int EPCR_ERPRW ; 
 int EPCR_WEP ; 
 int /*<<< orphan*/  dm9000_wait_eeprom (struct board_info*) ; 
 int /*<<< orphan*/  iow (struct board_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
dm9000_write_eeprom(struct board_info *db, int offset, u8 *data)
{
	unsigned long flags;

	if (db->flags & DM9000_PLATF_NO_EEPROM)
		return;

	mutex_lock(&db->addr_lock);

	spin_lock_irqsave(&db->lock, flags);
	iow(db, DM9000_EPAR, offset);
	iow(db, DM9000_EPDRH, data[1]);
	iow(db, DM9000_EPDRL, data[0]);
	iow(db, DM9000_EPCR, EPCR_WEP | EPCR_ERPRW);
	spin_unlock_irqrestore(&db->lock, flags);

	dm9000_wait_eeprom(db);

	mdelay(1);	/* wait at least 150uS to clear */

	spin_lock_irqsave(&db->lock, flags);
	iow(db, DM9000_EPCR, 0);
	spin_unlock_irqrestore(&db->lock, flags);

	mutex_unlock(&db->addr_lock);
}