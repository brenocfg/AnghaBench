#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct ksz_device {TYPE_1__* dev_ops; } ;
struct dsa_switch {struct ksz_device* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* w_phy ) (struct ksz_device*,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ksz_device*,int,int,int /*<<< orphan*/ ) ; 

int ksz_phy_write16(struct dsa_switch *ds, int addr, int reg, u16 val)
{
	struct ksz_device *dev = ds->priv;

	dev->dev_ops->w_phy(dev, addr, reg, val);

	return 0;
}