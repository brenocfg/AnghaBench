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
struct tv_mode {int nbr_end; scalar_t__ progressive; } ;

/* Variables and functions */

__attribute__((used)) static int
intel_tv_mode_vdisplay(const struct tv_mode *tv_mode)
{
	if (tv_mode->progressive)
		return tv_mode->nbr_end + 1;
	else
		return 2 * (tv_mode->nbr_end + 1);
}