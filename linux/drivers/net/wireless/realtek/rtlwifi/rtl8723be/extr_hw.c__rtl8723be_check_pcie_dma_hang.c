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
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ REG_DBI_CTRL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int rtl_read_byte (struct rtl_priv*,scalar_t__) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,scalar_t__,int) ; 

__attribute__((used)) static bool _rtl8723be_check_pcie_dma_hang(struct rtl_priv *rtlpriv)
{
	u8 tmp;

	/* write reg 0x350 Bit[26]=1. Enable debug port. */
	tmp = rtl_read_byte(rtlpriv, REG_DBI_CTRL + 3);
	if (!(tmp & BIT(2))) {
		rtl_write_byte(rtlpriv, REG_DBI_CTRL + 3, (tmp | BIT(2)));
		mdelay(100); /* Suggested by DD Justin_tsai. */
	}

	/* read reg 0x350 Bit[25] if 1 : RX hang
	 * read reg 0x350 Bit[24] if 1 : TX hang
	 */
	tmp = rtl_read_byte(rtlpriv, REG_DBI_CTRL + 3);
	if ((tmp & BIT(0)) || (tmp & BIT(1))) {
		RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD,
			 "CheckPcieDMAHang8723BE(): true!!\n");
		return true;
	}
	return false;
}