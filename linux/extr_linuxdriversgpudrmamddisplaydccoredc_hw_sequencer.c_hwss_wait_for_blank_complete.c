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
struct timing_generator {TYPE_1__* funcs; } ;
struct TYPE_2__ {scalar_t__ (* is_blanked ) (struct timing_generator*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dm_error (char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ stub1 (struct timing_generator*) ; 

bool hwss_wait_for_blank_complete(
		struct timing_generator *tg)
{
	int counter;

	/* Not applicable if the pipe is not primary, save 300ms of boot time */
	if (!tg->funcs->is_blanked)
		return true;
	for (counter = 0; counter < 100; counter++) {
		if (tg->funcs->is_blanked(tg))
			break;

		msleep(1);
	}

	if (counter == 100) {
		dm_error("DC: failed to blank crtc!\n");
		return false;
	}

	return true;
}