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
struct wl1251 {int /*<<< orphan*/  intr_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_REG_INTERRUPT_MASK ; 
 int /*<<< orphan*/  HI_CFG ; 
 int /*<<< orphan*/  HI_CFG_DEF_VAL ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void wl1251_boot_target_enable_interrupts(struct wl1251 *wl)
{
	wl1251_reg_write32(wl, ACX_REG_INTERRUPT_MASK, ~(wl->intr_mask));
	wl1251_reg_write32(wl, HI_CFG, HI_CFG_DEF_VAL);
}