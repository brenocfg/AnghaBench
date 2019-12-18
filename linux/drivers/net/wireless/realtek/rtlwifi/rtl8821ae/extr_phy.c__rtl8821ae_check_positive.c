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
typedef  int u32 ;
struct rtl_priv {int dummy; } ;
struct rtl_hal {int version; scalar_t__ interface; int board_type; int package_type; int type_glna; int type_gpa; int type_alna; int type_apa; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int CHIP_VER_RTL_MASK ; 
 int CHIP_VER_RTL_SHIFT ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_TRACE ; 
 scalar_t__ INTF_USB ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 struct rtl_hal* rtl_hal (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 

__attribute__((used)) static bool _rtl8821ae_check_positive(struct ieee80211_hw *hw,
				      const u32 condition1,
				      const u32 condition2)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	u32 cut_ver = ((rtlhal->version & CHIP_VER_RTL_MASK)
					>> CHIP_VER_RTL_SHIFT);
	u32 intf = (rtlhal->interface == INTF_USB ? BIT(1) : BIT(0));

	u8  board_type = ((rtlhal->board_type & BIT(4)) >> 4) << 0 | /* _GLNA */
			 ((rtlhal->board_type & BIT(3)) >> 3) << 1 | /* _GPA  */
			 ((rtlhal->board_type & BIT(7)) >> 7) << 2 | /* _ALNA */
			 ((rtlhal->board_type & BIT(6)) >> 6) << 3 | /* _APA  */
			 ((rtlhal->board_type & BIT(2)) >> 2) << 4;  /* _BT   */

	u32 cond1 = condition1, cond2 = condition2;
	u32 driver1 = cut_ver << 24 |	/* CUT ver */
		      0 << 20 |			/* interface 2/2 */
		      0x04 << 16 |		/* platform */
		      rtlhal->package_type << 12 |
		      intf << 8 |			/* interface 1/2 */
		      board_type;

	u32 driver2 = rtlhal->type_glna <<  0 |
		      rtlhal->type_gpa  <<  8 |
		      rtlhal->type_alna << 16 |
		      rtlhal->type_apa  << 24;

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "===> [8812A] CheckPositive (cond1, cond2) = (0x%X 0x%X)\n",
		 cond1, cond2);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "===> [8812A] CheckPositive (driver1, driver2) = (0x%X 0x%X)\n",
		 driver1, driver2);

	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "	(Platform, Interface) = (0x%X, 0x%X)\n", 0x04, intf);
	RT_TRACE(rtlpriv, COMP_INIT, DBG_TRACE,
		 "	(Board, Package) = (0x%X, 0x%X)\n",
		 rtlhal->board_type, rtlhal->package_type);

	/*============== Value Defined Check ===============*/
	/*QFN Type [15:12] and Cut Version [27:24] need to do value check*/

	if (((cond1 & 0x0000F000) != 0) && ((cond1 & 0x0000F000) !=
		(driver1 & 0x0000F000)))
		return false;
	if (((cond1 & 0x0F000000) != 0) && ((cond1 & 0x0F000000) !=
		(driver1 & 0x0F000000)))
		return false;

	/*=============== Bit Defined Check ================*/
	/* We don't care [31:28] */

	cond1   &= 0x00FF0FFF;
	driver1 &= 0x00FF0FFF;

	if ((cond1 & driver1) == cond1) {
		u32 mask = 0;

		if ((cond1 & 0x0F) == 0) /* BoardType is DONTCARE*/
			return true;

		if ((cond1 & BIT(0)) != 0) /*GLNA*/
			mask |= 0x000000FF;
		if ((cond1 & BIT(1)) != 0) /*GPA*/
			mask |= 0x0000FF00;
		if ((cond1 & BIT(2)) != 0) /*ALNA*/
			mask |= 0x00FF0000;
		if ((cond1 & BIT(3)) != 0) /*APA*/
			mask |= 0xFF000000;

		/* BoardType of each RF path is matched*/
		if ((cond2 & mask) == (driver2 & mask))
			return true;
		else
			return false;
	} else
		return false;
}