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
typedef  int u16 ;
struct rtl_priv {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_DBI_ADDR ; 
 int REG_DBI_FLAG ; 
 int REG_DBI_WDATA ; 
 int rtl_read_byte (struct rtl_priv*,int) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int,int) ; 
 int /*<<< orphan*/  rtl_write_word (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void _rtl8723be_dbi_write(struct rtl_priv *rtlpriv, u16 addr, u8 data)
{
	u8 tmp = 0, count = 0;
	u16 write_addr = 0, remainder = addr % 4;

	/* Write DBI 1Byte Data */
	write_addr = REG_DBI_WDATA + remainder;
	rtl_write_byte(rtlpriv, write_addr, data);

	/* Write DBI 2Byte Address & Write Enable */
	write_addr = (addr & 0xfffc) | (BIT(0) << (remainder + 12));
	rtl_write_word(rtlpriv, REG_DBI_ADDR, write_addr);

	/* Write DBI Write Flag */
	rtl_write_byte(rtlpriv, REG_DBI_FLAG, 0x1);

	tmp = rtl_read_byte(rtlpriv, REG_DBI_FLAG);
	count = 0;
	while (tmp && count < 20) {
		udelay(10);
		tmp = rtl_read_byte(rtlpriv, REG_DBI_FLAG);
		count++;
	}
}