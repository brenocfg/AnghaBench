#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int* status_ptr; TYPE_1__** status; } ;
struct TYPE_4__ {unsigned long when; int /*<<< orphan*/  ssr; int /*<<< orphan*/  ph; int /*<<< orphan*/  irq; } ;
typedef  TYPE_2__ AS_Host ;

/* Variables and functions */
 int STATUS_BUFFER_SIZE ; 
 int STATUS_BUFFER_TO_PRINT ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void
acornscsi_dumplogline(AS_Host *host, int target, int line)
{
	unsigned long prev;
	signed int ptr;

	ptr = host->status_ptr[target] - STATUS_BUFFER_TO_PRINT;
	if (ptr < 0)
		ptr += STATUS_BUFFER_SIZE;

	printk("%c: %3s:", target == 8 ? 'H' : '0' + target,
		line == 0 ? "ph" : line == 1 ? "ssr" : "int");

	prev = host->status[target][ptr].when;

	for (; ptr != host->status_ptr[target]; ptr = (ptr + 1) & (STATUS_BUFFER_SIZE - 1)) {
		unsigned long time_diff;

		if (!host->status[target][ptr].when)
			continue;

		switch (line) {
		case 0:
			printk("%c%02X", host->status[target][ptr].irq ? '-' : ' ',
					 host->status[target][ptr].ph);
			break;

		case 1:
			printk(" %02X", host->status[target][ptr].ssr);
			break;

		case 2:
			time_diff = host->status[target][ptr].when - prev;
			prev = host->status[target][ptr].when;
			if (time_diff == 0)
				printk("==^");
			else if (time_diff >= 100)
				printk("   ");
			else
				printk(" %02ld", time_diff);
			break;
		}
	}

	printk("\n");
}