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
struct sfax_hw {scalar_t__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  ISAR_IRQBIT ; 
 scalar_t__ TIGER_AUX_IRQMASK ; 
 int /*<<< orphan*/  WriteISAC_IND (struct sfax_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteISAR_IND (struct sfax_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
disable_hwirq(struct sfax_hw *sf)
{
	WriteISAC_IND(sf, ISAC_MASK, 0xFF);
	WriteISAR_IND(sf, ISAR_IRQBIT, 0);
	outb(0, sf->cfg + TIGER_AUX_IRQMASK);
}