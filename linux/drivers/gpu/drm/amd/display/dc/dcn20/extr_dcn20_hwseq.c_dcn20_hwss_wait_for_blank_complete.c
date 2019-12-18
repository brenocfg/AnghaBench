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
struct output_pixel_processor {TYPE_1__* funcs; } ;
struct TYPE_2__ {scalar_t__ (* dpg_is_blanked ) (struct output_pixel_processor*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dm_error (char*) ; 
 scalar_t__ stub1 (struct output_pixel_processor*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool dcn20_hwss_wait_for_blank_complete(
		struct output_pixel_processor *opp)
{
	int counter;

	for (counter = 0; counter < 1000; counter++) {
		if (opp->funcs->dpg_is_blanked(opp))
			break;

		udelay(100);
	}

	if (counter == 1000) {
		dm_error("DC: failed to blank crtc!\n");
		return false;
	}

	return true;
}