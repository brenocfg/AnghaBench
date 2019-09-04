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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 unsigned int sun4v_build_cookie (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int sun4v_build_sysino (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sun4v_cookie_only_virqs () ; 

unsigned int sun4v_build_irq(u32 devhandle, unsigned int devino)
{
	unsigned int irq;

	if (sun4v_cookie_only_virqs())
		irq = sun4v_build_cookie(devhandle, devino);
	else
		irq = sun4v_build_sysino(devhandle, devino);

	return irq;
}