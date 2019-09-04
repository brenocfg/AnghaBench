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
struct timing_generator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  optc1_blank_crtc (struct timing_generator*) ; 
 int /*<<< orphan*/  optc1_unblank_crtc (struct timing_generator*) ; 

void optc1_set_blank(struct timing_generator *optc,
		bool enable_blanking)
{
	if (enable_blanking)
		optc1_blank_crtc(optc);
	else
		optc1_unblank_crtc(optc);
}