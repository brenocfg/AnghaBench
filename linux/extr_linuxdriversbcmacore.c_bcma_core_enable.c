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
typedef  int u32 ;
struct bcma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCMA_IOCTL ; 
 int BCMA_IOCTL_CLK ; 
 int BCMA_IOCTL_FGC ; 
 int /*<<< orphan*/  BCMA_RESET_CTL ; 
 int /*<<< orphan*/  bcma_aread32 (struct bcma_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcma_awrite32 (struct bcma_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bcma_core_disable (struct bcma_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int bcma_core_enable(struct bcma_device *core, u32 flags)
{
	bcma_core_disable(core, flags);

	bcma_awrite32(core, BCMA_IOCTL, (BCMA_IOCTL_CLK | BCMA_IOCTL_FGC | flags));
	bcma_aread32(core, BCMA_IOCTL);

	bcma_awrite32(core, BCMA_RESET_CTL, 0);
	bcma_aread32(core, BCMA_RESET_CTL);
	udelay(1);

	bcma_awrite32(core, BCMA_IOCTL, (BCMA_IOCTL_CLK | flags));
	bcma_aread32(core, BCMA_IOCTL);
	udelay(1);

	return 0;
}