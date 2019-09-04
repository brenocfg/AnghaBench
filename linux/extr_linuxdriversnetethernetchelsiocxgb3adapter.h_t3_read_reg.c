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
typedef  scalar_t__ u32 ;
struct adapter {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CH_DBG (struct adapter*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  MMIO ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static inline u32 t3_read_reg(struct adapter *adapter, u32 reg_addr)
{
	u32 val = readl(adapter->regs + reg_addr);

	CH_DBG(adapter, MMIO, "read register 0x%x value 0x%x\n", reg_addr, val);
	return val;
}