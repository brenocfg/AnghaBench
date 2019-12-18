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
struct jme_adapter {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  reg_dbg (struct jme_adapter*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void jwrite32f(struct jme_adapter *jme, u32 reg, u32 val)
{
	/*
	 * Read after write should cause flush
	 */
	reg_dbg(jme, "REG WRITE FLUSH", val, reg);
	writel(val, jme->regs + reg);
	readl(jme->regs + reg);
	reg_dbg(jme, "VAL AFTER WRITE", readl(jme->regs + reg), reg);
}