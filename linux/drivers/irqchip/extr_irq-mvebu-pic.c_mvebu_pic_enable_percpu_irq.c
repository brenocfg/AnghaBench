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
struct mvebu_pic {int /*<<< orphan*/  parent_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_TYPE_NONE ; 
 int /*<<< orphan*/  enable_percpu_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvebu_pic_reset (struct mvebu_pic*) ; 

__attribute__((used)) static void mvebu_pic_enable_percpu_irq(void *data)
{
	struct mvebu_pic *pic = data;

	mvebu_pic_reset(pic);
	enable_percpu_irq(pic->parent_irq, IRQ_TYPE_NONE);
}