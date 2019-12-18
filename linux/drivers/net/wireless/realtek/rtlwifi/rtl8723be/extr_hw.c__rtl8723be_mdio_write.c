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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_MDIO_CTL ; 
 int /*<<< orphan*/  REG_MDIO_WDATA ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl8723be_mdio_write(struct rtl_priv *rtlpriv, u8 addr, u16 data)
{
	u8 tmp = 0, count = 0;

	rtl_write_word(rtlpriv, REG_MDIO_WDATA, data);
	rtl_write_byte(rtlpriv, REG_MDIO_CTL, addr | BIT(5));
	tmp = rtl_read_byte(rtlpriv, REG_MDIO_CTL) & BIT(5);
	count = 0;
	while (tmp && count < 20) {
		udelay(10);
		tmp = rtl_read_byte(rtlpriv, REG_MDIO_CTL) & BIT(5);
		count++;
	}
}