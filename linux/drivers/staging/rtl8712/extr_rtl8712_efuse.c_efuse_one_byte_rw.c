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
typedef  int u16 ;
struct _adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ EFUSE_CTRL ; 
 int r8712_read8 (struct _adapter*,scalar_t__) ; 
 int /*<<< orphan*/  r8712_write8 (struct _adapter*,scalar_t__,int) ; 

__attribute__((used)) static u8 efuse_one_byte_rw(struct _adapter *adapter, u8 bRead, u16 addr,
			    u8 *data)
{
	u8 tmpidx = 0, tmpv8 = 0, bResult;

	/* -----------------e-fuse reg ctrl --------------------------------- */
	r8712_write8(adapter, EFUSE_CTRL + 1, (u8)(addr & 0xFF)); /* address */
	tmpv8 = ((u8)((addr >> 8) & 0x03)) |
		 (r8712_read8(adapter, EFUSE_CTRL + 2) & 0xFC);
	r8712_write8(adapter, EFUSE_CTRL + 2, tmpv8);
	if (bRead) {
		r8712_write8(adapter, EFUSE_CTRL + 3,  0x72); /* read cmd */
		while (!(0x80 & r8712_read8(adapter, EFUSE_CTRL + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100) {
			*data = r8712_read8(adapter, EFUSE_CTRL);
			bResult = true;
		} else {
			*data = 0;
			bResult = false;
		}
	} else {
		r8712_write8(adapter, EFUSE_CTRL, *data); /* data */
		r8712_write8(adapter, EFUSE_CTRL + 3, 0xF2); /* write cmd */
		while ((0x80 & r8712_read8(adapter, EFUSE_CTRL + 3)) &&
		       (tmpidx < 100))
			tmpidx++;
		if (tmpidx < 100)
			bResult = true;
		else
			bResult = false;
	}
	return bResult;
}