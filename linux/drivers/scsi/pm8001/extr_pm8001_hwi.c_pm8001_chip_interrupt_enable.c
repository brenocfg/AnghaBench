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
typedef  int /*<<< orphan*/  u8 ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pm8001_chip_intx_interrupt_enable (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  pm8001_chip_msix_interrupt_enable (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pm8001_chip_interrupt_enable(struct pm8001_hba_info *pm8001_ha, u8 vec)
{
#ifdef PM8001_USE_MSIX
	pm8001_chip_msix_interrupt_enable(pm8001_ha, 0);
#else
	pm8001_chip_intx_interrupt_enable(pm8001_ha);
#endif
}