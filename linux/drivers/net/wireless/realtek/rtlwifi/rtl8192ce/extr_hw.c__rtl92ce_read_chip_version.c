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
typedef  int u32 ;
struct rtl_phy {scalar_t__ rf_type; } ;
struct rtl_priv {struct rtl_phy phy; } ;
struct ieee80211_hw {int dummy; } ;
typedef  enum version_8192c { ____Placeholder_version_8192c } version_8192c ;

/* Variables and functions */
 int BIT (int) ; 
#define  CHIP_88C 140 
#define  CHIP_92C 139 
#define  CHIP_92C_1T2R 138 
 int CHIP_92C_BITMASK ; 
 scalar_t__ CHIP_BONDING_92C_1T2R ; 
 scalar_t__ CHIP_BONDING_IDENTIFIER (int) ; 
 int CHIP_UNKNOWN ; 
 int CHIP_VENDOR_UMC ; 
 int CHIP_VENDOR_UMC_B_CUT ; 
 int CHIP_VER_B ; 
 int CHIP_VER_RTL_MASK ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ IS_92C_SERIAL (int) ; 
 int /*<<< orphan*/  IS_CHIP_VENDOR_UMC (int) ; 
 int /*<<< orphan*/  REG_HPON_FSM ; 
 int /*<<< orphan*/  REG_SYS_CFG ; 
 void* RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
 int RF_TYPE_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int TRP_VAUX_EN ; 
 int TYPE_ID ; 
 int VENDOR_ID ; 
#define  VERSION_A_CHIP_88C 137 
#define  VERSION_A_CHIP_92C 136 
#define  VERSION_B_CHIP_88C 135 
#define  VERSION_B_CHIP_92C 134 
#define  VERSION_NORMAL_UMC_CHIP_88C_A_CUT 133 
#define  VERSION_NORMAL_UMC_CHIP_88C_B_CUT 132 
#define  VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT 131 
#define  VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT 130 
#define  VERSION_NORMAL_UMC_CHIP_92C_A_CUT 129 
#define  VERSION_NORMAL_UMC_CHIP_92C_B_CUT 128 
 int VERSION_UNKNOWN ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,char const*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int rtl_read_dword (struct rtl_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum version_8192c _rtl92ce_read_chip_version(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	enum version_8192c version = VERSION_UNKNOWN;
	u32 value32;
	const char *versionid;

	value32 = rtl_read_dword(rtlpriv, REG_SYS_CFG);
	if (value32 & TRP_VAUX_EN) {
		version = (value32 & TYPE_ID) ? VERSION_A_CHIP_92C :
			   VERSION_A_CHIP_88C;
	} else {
		version = (enum version_8192c) (CHIP_VER_B |
				((value32 & TYPE_ID) ? CHIP_92C_BITMASK : 0) |
				((value32 & VENDOR_ID) ? CHIP_VENDOR_UMC : 0));
		if ((!IS_CHIP_VENDOR_UMC(version)) && (value32 &
		     CHIP_VER_RTL_MASK)) {
			version = (enum version_8192c)(version |
				   ((((value32 & CHIP_VER_RTL_MASK) == BIT(12))
				   ? CHIP_VENDOR_UMC_B_CUT : CHIP_UNKNOWN) |
				   CHIP_VENDOR_UMC));
		}
		if (IS_92C_SERIAL(version)) {
			value32 = rtl_read_dword(rtlpriv, REG_HPON_FSM);
			version = (enum version_8192c)(version |
				   ((CHIP_BONDING_IDENTIFIER(value32)
				   == CHIP_BONDING_92C_1T2R) ?
				   RF_TYPE_1T2R : 0));
		}
	}

	switch (version) {
	case VERSION_B_CHIP_92C:
		versionid = "B_CHIP_92C";
		break;
	case VERSION_B_CHIP_88C:
		versionid = "B_CHIP_88C";
		break;
	case VERSION_A_CHIP_92C:
		versionid = "A_CHIP_92C";
		break;
	case VERSION_A_CHIP_88C:
		versionid = "A_CHIP_88C";
		break;
	case VERSION_NORMAL_UMC_CHIP_92C_1T2R_A_CUT:
		versionid = "A_CUT_92C_1T2R";
		break;
	case VERSION_NORMAL_UMC_CHIP_92C_A_CUT:
		versionid = "A_CUT_92C";
		break;
	case VERSION_NORMAL_UMC_CHIP_88C_A_CUT:
		versionid = "A_CUT_88C";
		break;
	case VERSION_NORMAL_UMC_CHIP_92C_1T2R_B_CUT:
		versionid = "B_CUT_92C_1T2R";
		break;
	case VERSION_NORMAL_UMC_CHIP_92C_B_CUT:
		versionid = "B_CUT_92C";
		break;
	case VERSION_NORMAL_UMC_CHIP_88C_B_CUT:
		versionid = "B_CUT_88C";
		break;
	default:
		versionid = "Unknown. Bug?";
		break;
	}

	pr_info("Chip Version ID: %s\n", versionid);

	switch (version & 0x3) {
	case CHIP_88C:
		rtlphy->rf_type = RF_1T1R;
		break;
	case CHIP_92C:
		rtlphy->rf_type = RF_2T2R;
		break;
	case CHIP_92C_1T2R:
		rtlphy->rf_type = RF_1T2R;
		break;
	default:
		rtlphy->rf_type = RF_1T1R;
		pr_err("ERROR RF_Type is set!!\n");
		break;
	}

	RT_TRACE(rtlpriv, COMP_INIT, DBG_LOUD, "Chip RF Type: %s\n",
		 rtlphy->rf_type == RF_2T2R ? "RF_2T2R" : "RF_1T1R");

	return version;
}