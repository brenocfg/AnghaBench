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
struct xenfb_info {int irq; scalar_t__ update_wanted; } ;

/* Variables and functions */
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenfb_info*) ; 

__attribute__((used)) static void xenfb_disconnect_backend(struct xenfb_info *info)
{
	/* Prevent xenfb refresh */
	info->update_wanted = 0;
	if (info->irq >= 0)
		unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
}