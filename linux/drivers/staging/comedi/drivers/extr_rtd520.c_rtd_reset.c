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
struct rtd_private {scalar_t__ lcfg; } ;
struct comedi_device {scalar_t__ mmio; struct rtd_private* private; } ;

/* Variables and functions */
 scalar_t__ LAS0_BOARD_RESET ; 
 scalar_t__ LAS0_CLEAR ; 
 scalar_t__ LAS0_IT ; 
 scalar_t__ PLX_REG_INTCSR ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtd_reset(struct comedi_device *dev)
{
	struct rtd_private *devpriv = dev->private;

	writel(0, dev->mmio + LAS0_BOARD_RESET);
	usleep_range(100, 1000);	/* needed? */
	writel(0, devpriv->lcfg + PLX_REG_INTCSR);
	writew(0, dev->mmio + LAS0_IT);
	writew(~0, dev->mmio + LAS0_CLEAR);
	readw(dev->mmio + LAS0_CLEAR);
}