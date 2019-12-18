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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X_SEL (void*,char*,...) ; 
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,...) ; 
 int /*<<< orphan*/  rtw_read32 (struct adapter*,int) ; 

void bb_reg_dump(void *sel, struct adapter *adapter)
{
	int i, j = 1;

	DBG_871X_SEL_NL(sel, "======= BB REG =======\n");
	for (i = 0x800; i < 0x1000 ; i += 4) {
		if (j%4 == 1)
			DBG_871X_SEL_NL(sel, "0x%03x", i);
		DBG_871X_SEL(sel, " 0x%08x ", rtw_read32(adapter, i));
		if ((j++)%4 == 0)
			DBG_871X_SEL(sel, "\n");
	}
}