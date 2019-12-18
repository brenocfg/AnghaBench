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
struct komeda_crtc {TYPE_1__* master; } ;
struct TYPE_2__ {scalar_t__ dual_link; } ;

/* Variables and functions */

__attribute__((used)) static unsigned long
komeda_calc_min_aclk_rate(struct komeda_crtc *kcrtc,
			  unsigned long pxlclk)
{
	/* Once dual-link one display pipeline drives two display outputs,
	 * the aclk needs run on the double rate of pxlclk
	 */
	if (kcrtc->master->dual_link)
		return pxlclk * 2;
	else
		return pxlclk;
}