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
struct xenkbd_info {int irq; int gref; } ;

/* Variables and functions */
 int /*<<< orphan*/  gnttab_end_foreign_access (int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unbind_from_irqhandler (int,struct xenkbd_info*) ; 

__attribute__((used)) static void xenkbd_disconnect_backend(struct xenkbd_info *info)
{
	if (info->irq >= 0)
		unbind_from_irqhandler(info->irq, info);
	info->irq = -1;
	if (info->gref >= 0)
		gnttab_end_foreign_access(info->gref, 0, 0UL);
	info->gref = -1;
}