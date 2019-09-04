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

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ TZIC_DSMINT ; 
 scalar_t__ TZIC_ENSET0 (unsigned int) ; 
 scalar_t__ TZIC_WAKEUP0 (unsigned int) ; 
 int imx_readl (scalar_t__) ; 
 int /*<<< orphan*/  imx_writel (int,scalar_t__) ; 
 scalar_t__ tzic_base ; 
 scalar_t__ unlikely (int) ; 

int tzic_enable_wake(void)
{
	unsigned int i;

	imx_writel(1, tzic_base + TZIC_DSMINT);
	if (unlikely(imx_readl(tzic_base + TZIC_DSMINT) == 0))
		return -EAGAIN;

	for (i = 0; i < 4; i++)
		imx_writel(imx_readl(tzic_base + TZIC_ENSET0(i)),
			   tzic_base + TZIC_WAKEUP0(i));

	return 0;
}