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
struct TYPE_2__ {void (* handler ) (unsigned char*,int,int) ;int busy; } ;

/* Variables and functions */
 scalar_t__ adb_got_sleep ; 
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_handler_lock ; 
 int /*<<< orphan*/  pr_cont (char*,int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 void stub1 (unsigned char*,int,int) ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
adb_input(unsigned char *buf, int nb, int autopoll)
{
	int i, id;
	static int dump_adb_input;
	unsigned long flags;
	
	void (*handler)(unsigned char *, int, int);

	/* We skip keystrokes and mouse moves when the sleep process
	 * has been started. We stop autopoll, but this is another security
	 */
	if (adb_got_sleep)
		return;
		
	id = buf[0] >> 4;
	if (dump_adb_input) {
		pr_info("adb packet: ");
		for (i = 0; i < nb; ++i)
			pr_cont(" %x", buf[i]);
		pr_cont(", id = %d\n", id);
	}
	write_lock_irqsave(&adb_handler_lock, flags);
	handler = adb_handler[id].handler;
	if (handler != NULL)
		adb_handler[id].busy = 1;
	write_unlock_irqrestore(&adb_handler_lock, flags);
	if (handler != NULL) {
		(*handler)(buf, nb, autopoll);
		wmb();
		adb_handler[id].busy = 0;
	}
		
}