#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct rtl8xxxu_reg8val {int reg; int val; } ;
struct rtl8xxxu_priv {scalar_t__ rtl_chip; TYPE_1__* udev; TYPE_2__* fops; } ;
struct TYPE_4__ {struct rtl8xxxu_reg8val* mactable; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int REG_MAX_AGGR_NUM ; 
 scalar_t__ RTL8192E ; 
 scalar_t__ RTL8723B ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int,int) ; 
 int rtl8xxxu_write8 (struct rtl8xxxu_priv*,int,int) ; 

__attribute__((used)) static int
rtl8xxxu_init_mac(struct rtl8xxxu_priv *priv)
{
	struct rtl8xxxu_reg8val *array = priv->fops->mactable;
	int i, ret;
	u16 reg;
	u8 val;

	for (i = 0; ; i++) {
		reg = array[i].reg;
		val = array[i].val;

		if (reg == 0xffff && val == 0xff)
			break;

		ret = rtl8xxxu_write8(priv, reg, val);
		if (ret != 1) {
			dev_warn(&priv->udev->dev,
				 "Failed to initialize MAC "
				 "(reg: %04x, val %02x)\n", reg, val);
			return -EAGAIN;
		}
	}

	if (priv->rtl_chip != RTL8723B && priv->rtl_chip != RTL8192E)
		rtl8xxxu_write8(priv, REG_MAX_AGGR_NUM, 0x0a);

	return 0;
}