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
struct resources {scalar_t__ bch_regs; } ;
struct gpmi_nand_data {struct resources resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  BM_BCH_CTRL_COMPLETE_IRQ ; 
 scalar_t__ HW_BCH_CTRL_CLR ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void gpmi_clear_bch(struct gpmi_nand_data *this)
{
	struct resources *r = &this->resources;
	writel(BM_BCH_CTRL_COMPLETE_IRQ, r->bch_regs + HW_BCH_CTRL_CLR);
}