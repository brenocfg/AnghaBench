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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct chv_pinctrl {scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_physical_address ;

/* Variables and functions */
 scalar_t__ ACPI_READ ; 
 scalar_t__ ACPI_WRITE ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  chv_lock ; 
 int /*<<< orphan*/  chv_writel (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static acpi_status chv_pinctrl_mmio_access_handler(u32 function,
	acpi_physical_address address, u32 bits, u64 *value,
	void *handler_context, void *region_context)
{
	struct chv_pinctrl *pctrl = region_context;
	unsigned long flags;
	acpi_status ret = AE_OK;

	raw_spin_lock_irqsave(&chv_lock, flags);

	if (function == ACPI_WRITE)
		chv_writel((u32)(*value), pctrl->regs + (u32)address);
	else if (function == ACPI_READ)
		*value = readl(pctrl->regs + (u32)address);
	else
		ret = AE_BAD_PARAMETER;

	raw_spin_unlock_irqrestore(&chv_lock, flags);

	return ret;
}