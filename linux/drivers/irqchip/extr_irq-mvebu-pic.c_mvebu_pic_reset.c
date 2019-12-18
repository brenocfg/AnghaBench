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
struct mvebu_pic {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PIC_CAUSE ; 
 scalar_t__ PIC_MASK ; 
 int /*<<< orphan*/  PIC_MAX_IRQ_MASK ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void mvebu_pic_reset(struct mvebu_pic *pic)
{
	/* ACK and mask all interrupts */
	writel(0, pic->base + PIC_MASK);
	writel(PIC_MAX_IRQ_MASK, pic->base + PIC_CAUSE);
}