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
struct dispc_device {unsigned long tv_pclk_rate; } ;

/* Variables and functions */

void dispc_set_tv_pclk(struct dispc_device *dispc, unsigned long pclk)
{
	dispc->tv_pclk_rate = pclk;
}