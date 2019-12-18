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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ hil_busy () ; 
 int /*<<< orphan*/  hil_command (unsigned char) ; 
 TYPE_1__ hil_dev ; 
 int /*<<< orphan*/  hil_write_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hil_do(unsigned char cmd, unsigned char *data, unsigned int len)
{
	unsigned long flags;

	spin_lock_irqsave(&hil_dev.lock, flags);
	while (hil_busy())
		/* wait */;
	hil_command(cmd);
	while (len--) {
		while (hil_busy())
			/* wait */;
		hil_write_data(*(data++));
	}
	spin_unlock_irqrestore(&hil_dev.lock, flags);
}