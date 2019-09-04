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
struct clk {int dummy; } ;

/* Variables and functions */
 scalar_t__ BCMCPU_IS_6328 () ; 
 scalar_t__ BCMCPU_IS_6362 () ; 
 scalar_t__ BCMCPU_IS_6368 () ; 
 int /*<<< orphan*/  CKCTL_6328_USBD_EN ; 
 int /*<<< orphan*/  CKCTL_6362_USBD_EN ; 
 int /*<<< orphan*/  CKCTL_6368_USBD_EN ; 
 int /*<<< orphan*/  bcm_hwclock_set (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void usbd_set(struct clk *clk, int enable)
{
	if (BCMCPU_IS_6328())
		bcm_hwclock_set(CKCTL_6328_USBD_EN, enable);
	else if (BCMCPU_IS_6362())
		bcm_hwclock_set(CKCTL_6362_USBD_EN, enable);
	else if (BCMCPU_IS_6368())
		bcm_hwclock_set(CKCTL_6368_USBD_EN, enable);
}