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
typedef  int /*<<< orphan*/  val ;
typedef  int u32 ;
typedef  int u16 ;
struct rtl8xxxu_reg32val {int reg; int val; } ;
struct rtl8xxxu_priv {TYPE_1__* udev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int rtl8xxxu_write32 (struct rtl8xxxu_priv*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

int rtl8xxxu_init_phy_regs(struct rtl8xxxu_priv *priv,
			   struct rtl8xxxu_reg32val *array)
{
	int i, ret;
	u16 reg;
	u32 val;

	for (i = 0; ; i++) {
		reg = array[i].reg;
		val = array[i].val;

		if (reg == 0xffff && val == 0xffffffff)
			break;

		ret = rtl8xxxu_write32(priv, reg, val);
		if (ret != sizeof(val)) {
			dev_warn(&priv->udev->dev,
				 "Failed to initialize PHY\n");
			return -EAGAIN;
		}
		udelay(1);
	}

	return 0;
}