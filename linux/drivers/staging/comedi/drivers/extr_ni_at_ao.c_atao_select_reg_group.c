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
struct comedi_device {scalar_t__ iobase; struct atao_private* private; } ;
struct atao_private {int /*<<< orphan*/  cfg1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATAO_CFG1_GRP2WR ; 
 scalar_t__ ATAO_CFG1_REG ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void atao_select_reg_group(struct comedi_device *dev, int group)
{
	struct atao_private *devpriv = dev->private;

	if (group)
		devpriv->cfg1 |= ATAO_CFG1_GRP2WR;
	else
		devpriv->cfg1 &= ~ATAO_CFG1_GRP2WR;
	outw(devpriv->cfg1, dev->iobase + ATAO_CFG1_REG);
}