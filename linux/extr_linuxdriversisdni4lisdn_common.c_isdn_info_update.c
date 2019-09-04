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
struct TYPE_3__ {int* private; scalar_t__ next; } ;
typedef  TYPE_1__ infostruct ;
struct TYPE_4__ {int /*<<< orphan*/  info_waitq; TYPE_1__* infochain; } ;

/* Variables and functions */
 TYPE_2__* dev ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
isdn_info_update(void)
{
	infostruct *p = dev->infochain;

	while (p) {
		*(p->private) = 1;
		p = (infostruct *) p->next;
	}
	wake_up_interruptible(&(dev->info_waitq));
}