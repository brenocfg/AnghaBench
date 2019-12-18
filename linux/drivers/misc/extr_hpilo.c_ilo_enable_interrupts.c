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
struct ilo_hwinfo {int /*<<< orphan*/ * mmio_vaddr; } ;

/* Variables and functions */
 size_t DB_IRQ ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void ilo_enable_interrupts(struct ilo_hwinfo *hw)
{
	iowrite8(ioread8(&hw->mmio_vaddr[DB_IRQ]) | 1, &hw->mmio_vaddr[DB_IRQ]);
}