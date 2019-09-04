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
typedef  int /*<<< orphan*/  u32 ;
struct ivtv {int /*<<< orphan*/  irqmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_IRQMASK ; 
 int /*<<< orphan*/  write_reg_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ivtv_clear_irq_mask(struct ivtv *itv, u32 mask)
{
	itv->irqmask &= ~mask;
	write_reg_sync(itv->irqmask, IVTV_REG_IRQMASK);
}