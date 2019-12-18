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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_2__ {int curr_rateidx; } ;
struct _adapter {TYPE_1__ mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  RF_PATH_A ; 
 int /*<<< orphan*/  RF_SYN_G2 ; 
 int /*<<< orphan*/  r8712_rf_reg_write (struct _adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void r8712_SetDataRate(struct _adapter *pAdapter)
{
	u8 path = RF_PATH_A;
	u8 offset = RF_SYN_G2;
	u32 value;

	value = (pAdapter->mppriv.curr_rateidx < 4) ? 0x4440 : 0xF200;
	r8712_rf_reg_write(pAdapter, path, offset, value);
}