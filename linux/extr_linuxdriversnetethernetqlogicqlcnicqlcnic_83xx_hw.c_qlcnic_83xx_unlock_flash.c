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
struct qlcnic_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLCNIC_FLASH_LOCK_OWNER ; 
 int /*<<< orphan*/  QLCNIC_FLASH_UNLOCK ; 
 int /*<<< orphan*/  QLC_SHARED_REG_RD32 (struct qlcnic_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QLC_SHARED_REG_WR32 (struct qlcnic_adapter*,int /*<<< orphan*/ ,int) ; 

void qlcnic_83xx_unlock_flash(struct qlcnic_adapter *adapter)
{
	QLC_SHARED_REG_RD32(adapter, QLCNIC_FLASH_UNLOCK);
	QLC_SHARED_REG_WR32(adapter, QLCNIC_FLASH_LOCK_OWNER, 0xFF);
}