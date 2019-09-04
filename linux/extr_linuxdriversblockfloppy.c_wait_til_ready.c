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
struct TYPE_2__ {int reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_STATUS ; 
 int STATUS_READY ; 
 int fd_inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdc ; 
 scalar_t__ initialized ; 
 int /*<<< orphan*/  show_floppy () ; 

__attribute__((used)) static int wait_til_ready(void)
{
	int status;
	int counter;

	if (FDCS->reset)
		return -1;
	for (counter = 0; counter < 10000; counter++) {
		status = fd_inb(FD_STATUS);
		if (status & STATUS_READY)
			return status;
	}
	if (initialized) {
		DPRINT("Getstatus times out (%x) on fdc %d\n", status, fdc);
		show_floppy();
	}
	FDCS->reset = 1;
	return -1;
}