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
struct sisusb_usb_data {int haveconsole; int con_first; int con_last; int sisusb_cursor_loc; int sisusb_cursor_size_from; int sisusb_cursor_size_to; int sisusb_num_columns; int scrbuf_size; unsigned long scrbuf; int /*<<< orphan*/  lock; TYPE_1__* sisusb_dev; int /*<<< orphan*/  gfxinit; int /*<<< orphan*/  SiS_Pr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MAX_NR_CONSOLES ; 
 int /*<<< orphan*/  console_lock () ; 
 int /*<<< orphan*/  console_unlock () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int do_take_over_console (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sisusb_usb_data** mysisusbs ; 
 int /*<<< orphan*/  sisusb_con ; 
 int /*<<< orphan*/  sisusb_initialize (struct sisusb_usb_data*) ; 
 scalar_t__ sisusb_reset_text_mode (struct sisusb_usb_data*,int) ; 
 scalar_t__ vmalloc (int) ; 

int
sisusb_console_init(struct sisusb_usb_data *sisusb, int first, int last)
{
	int i, ret;

	mutex_lock(&sisusb->lock);

	/* Erm.. that should not happen */
	if (sisusb->haveconsole || !sisusb->SiS_Pr) {
		mutex_unlock(&sisusb->lock);
		return 1;
	}

	sisusb->con_first = first;
	sisusb->con_last  = last;

	if (first > last ||
	    first > MAX_NR_CONSOLES ||
	    last > MAX_NR_CONSOLES) {
		mutex_unlock(&sisusb->lock);
		return 1;
	}

	/* If gfxcore not initialized or no consoles given, quit graciously */
	if (!sisusb->gfxinit || first < 1 || last < 1) {
		mutex_unlock(&sisusb->lock);
		return 0;
	}

	sisusb->sisusb_cursor_loc       = -1;
	sisusb->sisusb_cursor_size_from = -1;
	sisusb->sisusb_cursor_size_to   = -1;

	/* Set up text mode (and upload  default font) */
	if (sisusb_reset_text_mode(sisusb, 1)) {
		mutex_unlock(&sisusb->lock);
		dev_err(&sisusb->sisusb_dev->dev, "Failed to set up text mode\n");
		return 1;
	}

	/* Initialize some gfx registers */
	sisusb_initialize(sisusb);

	for (i = first - 1; i <= last - 1; i++) {
		/* Save sisusb for our interface routines */
		mysisusbs[i] = sisusb;
	}

	/* Initial console setup */
	sisusb->sisusb_num_columns = 80;

	/* Use a 32K buffer (matches b8000-bffff area) */
	sisusb->scrbuf_size = 32 * 1024;

	/* Allocate screen buffer */
	if (!(sisusb->scrbuf = (unsigned long)vmalloc(sisusb->scrbuf_size))) {
		mutex_unlock(&sisusb->lock);
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate screen buffer\n");
		return 1;
	}

	mutex_unlock(&sisusb->lock);

	/* Now grab the desired console(s) */
	console_lock();
	ret = do_take_over_console(&sisusb_con, first - 1, last - 1, 0);
	console_unlock();
	if (!ret)
		sisusb->haveconsole = 1;
	else {
		for (i = first - 1; i <= last - 1; i++)
			mysisusbs[i] = NULL;
	}

	return ret;
}