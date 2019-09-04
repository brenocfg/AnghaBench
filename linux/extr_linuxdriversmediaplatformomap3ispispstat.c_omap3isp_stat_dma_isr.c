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
 int /*<<< orphan*/  __stat_isr (struct ispstat*,int) ; 

void omap3isp_stat_dma_isr(struct ispstat *stat)
{
	__stat_isr(stat, 1);
}