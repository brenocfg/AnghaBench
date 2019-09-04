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
struct orion_mdio_dev {scalar_t__ regs; } ;

/* Variables and functions */
 int MVMDIO_XSMI_BUSY ; 
 scalar_t__ MVMDIO_XSMI_MGNT_REG ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int orion_mdio_xsmi_is_done(struct orion_mdio_dev *dev)
{
	return !(readl(dev->regs + MVMDIO_XSMI_MGNT_REG) & MVMDIO_XSMI_BUSY);
}