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
struct vscsifrnt_info {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  cond_resched () ; 
 scalar_t__ scsifront_cmd_done (struct vscsifrnt_info*) ; 

__attribute__((used)) static irqreturn_t scsifront_irq_fn(int irq, void *dev_id)
{
	struct vscsifrnt_info *info = dev_id;

	while (scsifront_cmd_done(info))
		/* Yield point for this unbounded loop. */
		cond_resched();

	return IRQ_HANDLED;
}