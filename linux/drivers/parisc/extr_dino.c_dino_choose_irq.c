#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int sversion; } ;
struct parisc_device {int /*<<< orphan*/  irq; TYPE_1__ id; } ;
struct dino_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dino_assign_irq (struct dino_device*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dino_choose_irq(struct parisc_device *dev, void *ctrl)
{
	int irq;
	struct dino_device *dino = ctrl;

	switch (dev->id.sversion) {
		case 0x00084:	irq =  8; break; /* PS/2 */
		case 0x0008c:	irq = 10; break; /* RS232 */
		case 0x00096:	irq =  8; break; /* PS/2 */
		default:	return;		 /* Unknown */
	}

	dino_assign_irq(dino, irq, &dev->irq);
}