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
typedef  int /*<<< orphan*/  u32 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ IOCMD_CTRL_REG ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ r8712_read32 (struct _adapter*,int) ; 
 int /*<<< orphan*/  r8712_write32 (struct _adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

u8 r8712_fw_cmd(struct _adapter *pAdapter, u32 cmd)
{
	int pollingcnts = 50;

	r8712_write32(pAdapter, IOCMD_CTRL_REG, cmd);
	msleep(100);
	while ((r8712_read32(pAdapter, IOCMD_CTRL_REG != 0)) &&
	       (pollingcnts > 0)) {
		pollingcnts--;
		msleep(20);
	}
	if (pollingcnts == 0)
		return false;
	return true;
}