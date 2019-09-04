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
struct gart_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ GART_ENTRY_ADDR ; 
 scalar_t__ GART_ENTRY_DATA ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static inline unsigned long gart_read_pte(struct gart_device *gart,
					  unsigned long offs)
{
	unsigned long pte;

	writel(offs, gart->regs + GART_ENTRY_ADDR);
	pte = readl(gart->regs + GART_ENTRY_DATA);

	return pte;
}