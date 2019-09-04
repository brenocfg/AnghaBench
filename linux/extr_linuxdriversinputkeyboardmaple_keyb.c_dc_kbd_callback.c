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
struct mapleq {TYPE_1__* recvbuf; struct maple_device* dev; } ;
struct maple_device {unsigned long function; } ;
struct dc_kbd {int /*<<< orphan*/  new; } ;
struct TYPE_2__ {scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_scan_kbd (struct dc_kbd*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 struct dc_kbd* maple_get_drvdata (struct maple_device*) ; 
 int /*<<< orphan*/  maple_keyb_mutex ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dc_kbd_callback(struct mapleq *mq)
{
	struct maple_device *mapledev = mq->dev;
	struct dc_kbd *kbd = maple_get_drvdata(mapledev);
	unsigned long *buf = (unsigned long *)(mq->recvbuf->buf);

	/*
	 * We should always get the lock because the only
	 * time it may be locked is if the driver is in the cleanup phase.
	 */
	if (likely(mutex_trylock(&maple_keyb_mutex))) {

		if (buf[1] == mapledev->function) {
			memcpy(kbd->new, buf + 2, 8);
			dc_scan_kbd(kbd);
		}

		mutex_unlock(&maple_keyb_mutex);
	}
}