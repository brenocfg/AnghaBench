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
typedef  int u8 ;
typedef  int u32 ;
struct rtl8xxxu_rfregval {int reg; int val; } ;
struct rtl8xxxu_priv {TYPE_1__* udev; } ;
typedef  enum rtl8xxxu_rfpath { ____Placeholder_rtl8xxxu_rfpath } rtl8xxxu_rfpath ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int rtl8xxxu_write_rfreg (struct rtl8xxxu_priv*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtl8xxxu_init_rf_regs(struct rtl8xxxu_priv *priv,
				 struct rtl8xxxu_rfregval *array,
				 enum rtl8xxxu_rfpath path)
{
	int i, ret;
	u8 reg;
	u32 val;

	for (i = 0; ; i++) {
		reg = array[i].reg;
		val = array[i].val;

		if (reg == 0xff && val == 0xffffffff)
			break;

		switch (reg) {
		case 0xfe:
			msleep(50);
			continue;
		case 0xfd:
			mdelay(5);
			continue;
		case 0xfc:
			mdelay(1);
			continue;
		case 0xfb:
			udelay(50);
			continue;
		case 0xfa:
			udelay(5);
			continue;
		case 0xf9:
			udelay(1);
			continue;
		}

		ret = rtl8xxxu_write_rfreg(priv, path, reg, val);
		if (ret) {
			dev_warn(&priv->udev->dev,
				 "Failed to initialize RF\n");
			return -EAGAIN;
		}
		udelay(1);
	}

	return 0;
}