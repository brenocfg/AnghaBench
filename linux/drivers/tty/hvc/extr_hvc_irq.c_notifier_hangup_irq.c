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
struct hvc_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  notifier_del_irq (struct hvc_struct*,int) ; 

void notifier_hangup_irq(struct hvc_struct *hp, int irq)
{
	notifier_del_irq(hp, irq);
}