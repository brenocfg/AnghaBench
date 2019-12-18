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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ GE_STATUS_OFF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int readl (scalar_t__) ; 
 scalar_t__ regbase ; 

int wmt_ge_sync(struct fb_info *p)
{
	int loops = 5000000;
	while ((readl(regbase + GE_STATUS_OFF) & 4) && --loops)
		cpu_relax();
	return loops > 0 ? 0 : -EBUSY;
}