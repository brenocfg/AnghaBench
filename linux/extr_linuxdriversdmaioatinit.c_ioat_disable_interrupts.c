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
struct ioatdma_device {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ IOAT_INTRCTRL_OFFSET ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ioat_disable_interrupts(struct ioatdma_device *ioat_dma)
{
	/* Disable all interrupt generation */
	writeb(0, ioat_dma->reg_base + IOAT_INTRCTRL_OFFSET);
}