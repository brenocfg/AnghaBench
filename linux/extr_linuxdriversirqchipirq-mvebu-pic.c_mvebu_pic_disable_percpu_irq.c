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
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvebu_pic_disable_percpu_irq(void *data)
{
	struct mvebu_pic *pic = data;

	disable_percpu_irq(pic->parent_irq);
}