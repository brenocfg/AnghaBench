#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {unsigned int pirq; unsigned int gsi; unsigned char flags; int /*<<< orphan*/  domid; } ;
struct TYPE_4__ {TYPE_1__ pirq; } ;
struct irq_info {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQT_PIRQ ; 
 struct irq_info* info_for_irq (unsigned int) ; 
 int xen_irq_info_common_setup (struct irq_info*,unsigned int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xen_irq_info_pirq_setup(unsigned irq,
				   unsigned evtchn,
				   unsigned pirq,
				   unsigned gsi,
				   uint16_t domid,
				   unsigned char flags)
{
	struct irq_info *info = info_for_irq(irq);

	info->u.pirq.pirq = pirq;
	info->u.pirq.gsi = gsi;
	info->u.pirq.domid = domid;
	info->u.pirq.flags = flags;

	return xen_irq_info_common_setup(info, irq, IRQT_PIRQ, evtchn, 0);
}