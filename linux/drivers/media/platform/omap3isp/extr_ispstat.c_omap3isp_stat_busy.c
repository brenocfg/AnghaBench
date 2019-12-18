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
struct ispstat {int buf_processing; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ ISPSTAT_DISABLED ; 
 int omap3isp_stat_pcr_busy (struct ispstat*) ; 

int omap3isp_stat_busy(struct ispstat *stat)
{
	return omap3isp_stat_pcr_busy(stat) | stat->buf_processing |
		(stat->state != ISPSTAT_DISABLED);
}