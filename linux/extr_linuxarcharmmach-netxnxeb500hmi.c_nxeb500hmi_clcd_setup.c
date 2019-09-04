#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; scalar_t__ msb_right; } ;
struct TYPE_5__ {TYPE_1__ green; } ;
struct TYPE_6__ {TYPE_2__ var; } ;
struct clcd_fb {TYPE_3__ fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETX_GPIO_CFG (int) ; 
 int /*<<< orphan*/  NETX_PIO_OEPIO ; 
 int /*<<< orphan*/  NETX_PIO_OUTPIO ; 
 int /*<<< orphan*/  NETX_SYSTEM_IOC_ACCESS_KEY ; 
 int /*<<< orphan*/  NETX_SYSTEM_IOC_CR ; 
 int netx_clcd_setup (struct clcd_fb*) ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nxeb500hmi_clcd_setup(struct clcd_fb *fb)
{
	unsigned int val;

	fb->fb.var.green.length = 5;
	fb->fb.var.green.msb_right = 0;

	/* enable asic control */
	val = readl(NETX_SYSTEM_IOC_ACCESS_KEY);
	writel(val, NETX_SYSTEM_IOC_ACCESS_KEY);

	writel(3, NETX_SYSTEM_IOC_CR);

	/* GPIO 14 is used for display enable on newer boards */
	writel(9, NETX_GPIO_CFG(14));

	val = readl(NETX_PIO_OUTPIO);
	writel(val | 1, NETX_PIO_OUTPIO);

	val = readl(NETX_PIO_OEPIO);
	writel(val | 1, NETX_PIO_OEPIO);
	return netx_clcd_setup(fb);
}