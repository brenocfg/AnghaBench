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
struct ispstat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp_stat_try_enable (struct ispstat*) ; 

void omap3isp_stat_isr_frame_sync(struct ispstat *stat)
{
	isp_stat_try_enable(stat);
}