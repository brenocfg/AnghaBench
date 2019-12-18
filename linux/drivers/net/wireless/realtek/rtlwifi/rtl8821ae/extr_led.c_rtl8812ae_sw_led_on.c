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
struct rtl_led {int ledon; int /*<<< orphan*/  ledpin; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  COMP_LED ; 
 int /*<<< orphan*/  DBG_LOUD ; 
#define  LED_PIN_GPIO0 130 
#define  LED_PIN_LED0 129 
#define  LED_PIN_LED1 128 
 int /*<<< orphan*/  REG_LEDCFG1 ; 
 int /*<<< orphan*/  REG_LEDCFG2 ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_byte (struct rtl_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_write_byte (struct rtl_priv*,int /*<<< orphan*/ ,int) ; 

void rtl8812ae_sw_led_on(struct ieee80211_hw *hw, struct rtl_led *pled)
{
	u16	ledreg = REG_LEDCFG1;
	u8	ledcfg = 0;
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	switch (pled->ledpin) {
	case LED_PIN_LED0:
		ledreg = REG_LEDCFG1;
		break;

	case LED_PIN_LED1:
		ledreg = REG_LEDCFG2;
		break;

	case LED_PIN_GPIO0:
	default:
		break;
	}

	RT_TRACE(rtlpriv, COMP_LED, DBG_LOUD,
		 "In SwLedOn, LedAddr:%X LEDPIN=%d\n",
		 ledreg, pled->ledpin);

	ledcfg =  rtl_read_byte(rtlpriv, ledreg);
	ledcfg |= BIT(5); /*Set 0x4c[21]*/
	ledcfg &= ~(BIT(7) | BIT(6) | BIT(3) | BIT(2) | BIT(1) | BIT(0));
		/*Clear 0x4c[23:22] and 0x4c[19:16]*/
	rtl_write_byte(rtlpriv, ledreg, ledcfg); /*SW control led0 on.*/
	pled->ledon = true;
}