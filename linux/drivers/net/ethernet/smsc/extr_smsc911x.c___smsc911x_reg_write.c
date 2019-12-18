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
struct smsc911x_data {int ioaddr; TYPE_1__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int SMSC911X_USE_16BIT ; 
 int SMSC911X_USE_32BIT ; 
 int /*<<< orphan*/  writel (int,int) ; 
 int /*<<< orphan*/  writew (int,int) ; 

__attribute__((used)) static inline void __smsc911x_reg_write(struct smsc911x_data *pdata, u32 reg,
					u32 val)
{
	if (pdata->config.flags & SMSC911X_USE_32BIT) {
		writel(val, pdata->ioaddr + reg);
		return;
	}

	if (pdata->config.flags & SMSC911X_USE_16BIT) {
		writew(val & 0xFFFF, pdata->ioaddr + reg);
		writew((val >> 16) & 0xFFFF, pdata->ioaddr + reg + 2);
		return;
	}

	BUG();
}