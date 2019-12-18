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
struct spa {int /*<<< orphan*/  reg_pe_handle; int /*<<< orphan*/  reg_tfc; int /*<<< orphan*/  reg_dar; int /*<<< orphan*/  reg_dsisr; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnv_ocxl_unmap_xsl_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_irq_registers(struct spa *spa)
{
	pnv_ocxl_unmap_xsl_regs(spa->reg_dsisr, spa->reg_dar, spa->reg_tfc,
				spa->reg_pe_handle);
}