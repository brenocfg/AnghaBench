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
typedef  long u32 ;
struct gart_device {int /*<<< orphan*/  dev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GART_ENTRY_ADDR ; 
 scalar_t__ GART_ENTRY_DATA ; 
 long GART_PAGE_MASK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,char*,unsigned long,long) ; 
 int /*<<< orphan*/  writel (long,scalar_t__) ; 

__attribute__((used)) static inline void gart_set_pte(struct gart_device *gart,
				unsigned long offs, u32 pte)
{
	writel(offs, gart->regs + GART_ENTRY_ADDR);
	writel(pte, gart->regs + GART_ENTRY_DATA);

	dev_dbg(gart->dev, "%s %08lx:%08x\n",
		 pte ? "map" : "unmap", offs, pte & GART_PAGE_MASK);
}