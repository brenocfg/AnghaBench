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
struct ds_status {int status; } ;
struct ds_device {int /*<<< orphan*/ * st_buf; int /*<<< orphan*/ * ep; } ;

/* Variables and functions */
 size_t EP_STATUS ; 
 int ST_EPOF ; 
 int ST_IDLE ; 
 int /*<<< orphan*/  ds_dump_status (struct ds_device*,int /*<<< orphan*/ *,int) ; 
 int ds_recv_status (struct ds_device*,struct ds_status*,int) ; 
 int /*<<< orphan*/  ds_reset_device (struct ds_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int ds_wait_status(struct ds_device *dev, struct ds_status *st)
{
	int err, count = 0;

	do {
		st->status = 0;
		err = ds_recv_status(dev, st, false);
#if 0
		if (err >= 0) {
			int i;
			printk("0x%x: count=%d, status: ", dev->ep[EP_STATUS], err);
			for (i = 0; i < err; ++i)
				printk("%02x ", dev->st_buf[i]);
			printk("\n");
		}
#endif
	} while (!(st->status & ST_IDLE) && !(err < 0) && ++count < 100);

	if (err >= 16 && st->status & ST_EPOF) {
		pr_info("Resetting device after ST_EPOF.\n");
		ds_reset_device(dev);
		/* Always dump the device status. */
		count = 101;
	}

	/* Dump the status for errors or if there is extended return data.
	 * The extended status includes new device detection (maybe someone
	 * can do something with it).
	 */
	if (err > 16 || count >= 100 || err < 0)
		ds_dump_status(dev, dev->st_buf, err);

	/* Extended data isn't an error.  Well, a short is, but the dump
	 * would have already told the user that and we can't do anything
	 * about it in software anyway.
	 */
	if (count >= 100 || err < 0)
		return -1;
	else
		return 0;
}