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
typedef  int u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int OPEN_RETRY_INTERVAL_PHY_0_3_OFFSET ; 
 int OPEN_RETRY_INTERVAL_PHY_0_3_SHIFT_ADDR ; 
 int OPEN_RETRY_INTERVAL_PHY_4_7_OFFSET ; 
 int OPEN_RETRY_INTERVAL_PHY_4_7_SHIFT_ADDR ; 
 int OPEN_RETRY_INTERVAL_REG_MASK ; 
 int pm8001_bar4_shift (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mpi_set_open_retry_interval_reg(struct pm8001_hba_info *pm8001_ha,
					    u32 interval)
{
	u32 offset;
	u32 value;
	u32 i;
	unsigned long flags;

#define OPEN_RETRY_INTERVAL_PHY_0_3_SHIFT_ADDR 0x00030000
#define OPEN_RETRY_INTERVAL_PHY_4_7_SHIFT_ADDR 0x00040000
#define OPEN_RETRY_INTERVAL_PHY_0_3_OFFSET 0x30B4
#define OPEN_RETRY_INTERVAL_PHY_4_7_OFFSET 0x30B4
#define OPEN_RETRY_INTERVAL_REG_MASK 0x0000FFFF

	value = interval & OPEN_RETRY_INTERVAL_REG_MASK;
	spin_lock_irqsave(&pm8001_ha->lock, flags);
	/* shift bar and set the OPEN_REJECT(RETRY) interval time of PHY 0 -3.*/
	if (-1 == pm8001_bar4_shift(pm8001_ha,
			     OPEN_RETRY_INTERVAL_PHY_0_3_SHIFT_ADDR)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		return;
	}
	for (i = 0; i < 4; i++) {
		offset = OPEN_RETRY_INTERVAL_PHY_0_3_OFFSET + 0x4000 * i;
		pm8001_cw32(pm8001_ha, 2, offset, value);
	}

	if (-1 == pm8001_bar4_shift(pm8001_ha,
			     OPEN_RETRY_INTERVAL_PHY_4_7_SHIFT_ADDR)) {
		spin_unlock_irqrestore(&pm8001_ha->lock, flags);
		return;
	}
	for (i = 4; i < 8; i++) {
		offset = OPEN_RETRY_INTERVAL_PHY_4_7_OFFSET + 0x4000 * (i-4);
		pm8001_cw32(pm8001_ha, 2, offset, value);
	}
	/*set the shifted destination address to 0x0 to avoid error operation */
	pm8001_bar4_shift(pm8001_ha, 0x0);
	spin_unlock_irqrestore(&pm8001_ha->lock, flags);
	return;
}