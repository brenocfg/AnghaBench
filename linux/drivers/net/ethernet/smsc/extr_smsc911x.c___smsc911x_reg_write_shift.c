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
struct TYPE_2__ {int flags; } ;
struct smsc911x_data {scalar_t__ ioaddr; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SMSC911X_USE_16BIT ; 
 int SMSC911X_USE_32BIT ; 
 scalar_t__ __smsc_shift (struct smsc911x_data*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static inline void
__smsc911x_reg_write_shift(struct smsc911x_data *pdata, u32 reg, u32 val)
{
	if (pdata->config.flags & SMSC911X_USE_32BIT) {
		writel(val, pdata->ioaddr + __smsc_shift(pdata, reg));
		return;
	}

	if (pdata->config.flags & SMSC911X_USE_16BIT) {
		writew(val & 0xFFFF,
			pdata->ioaddr + __smsc_shift(pdata, reg));
		writew((val >> 16) & 0xFFFF,
			pdata->ioaddr + __smsc_shift(pdata, reg + 2));
		return;
	}

	BUG();
}