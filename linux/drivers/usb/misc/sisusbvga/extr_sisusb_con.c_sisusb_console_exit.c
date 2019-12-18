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
struct sisusb_usb_data {void* font_backup; scalar_t__ scrbuf; scalar_t__ haveconsole; scalar_t__* havethisconsole; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  do_take_over_console (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sisusb_dummy_con ; 
 int /*<<< orphan*/  vfree (void*) ; 

void
sisusb_console_exit(struct sisusb_usb_data *sisusb)
{
	int i;

	/* This is called if the device is disconnected
	 * and while disconnect and lock semaphores
	 * are up. This should be save because we
	 * can't lose our sisusb any other way but by
	 * disconnection (and hence, the disconnect
	 * sema is for protecting all other access
	 * functions from disconnection, not the
	 * other way round).
	 */

	/* Now what do we do in case of disconnection:
	 * One alternative would be to simply call
	 * give_up_console(). Nah, not a good idea.
	 * give_up_console() is obviously buggy as it
	 * only discards the consw pointer from the
	 * driver_map, but doesn't adapt vc->vc_sw
	 * of the affected consoles. Hence, the next
	 * call to any of the console functions will
	 * eventually take a trip to oops county.
	 * Also, give_up_console for some reason
	 * doesn't decrement our module refcount.
	 * Instead, we switch our consoles to a private
	 * dummy console. This, of course, keeps our
	 * refcount up as well, but it works perfectly.
	 */

	if (sisusb->haveconsole) {
		for (i = 0; i < MAX_NR_CONSOLES; i++)
			if (sisusb->havethisconsole[i]) {
				console_lock();
				do_take_over_console(&sisusb_dummy_con, i, i, 0);
				console_unlock();
				/* At this point, con_deinit for all our
				 * consoles is executed by do_take_over_console().
				 */
			}
		sisusb->haveconsole = 0;
	}

	vfree((void *)sisusb->scrbuf);
	sisusb->scrbuf = 0;

	vfree(sisusb->font_backup);
	sisusb->font_backup = NULL;
}