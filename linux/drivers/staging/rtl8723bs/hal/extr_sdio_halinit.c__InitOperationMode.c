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
typedef  int /*<<< orphan*/  u8 ;
struct mlme_ext_priv {int cur_wireless_mode; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BW_OPMODE_20MHZ ; 
 int /*<<< orphan*/  BW_OPMODE_5G ; 
 int /*<<< orphan*/  REG_BWOPMODE ; 
#define  WIRELESS_MODE_A 133 
#define  WIRELESS_MODE_AUTO 132 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 int /*<<< orphan*/  rtw_write8 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitOperationMode(struct adapter *padapter)
{
	struct mlme_ext_priv *pmlmeext;
	u8 regBwOpMode = 0;

	pmlmeext = &padapter->mlmeextpriv;

	/* 1 This part need to modified according to the rate set we filtered!! */
	/*  */
	/*  Set RRSR, RATR, and REG_BWOPMODE registers */
	/*  */
	switch (pmlmeext->cur_wireless_mode) {
	case WIRELESS_MODE_B:
		regBwOpMode = BW_OPMODE_20MHZ;
		break;
	case WIRELESS_MODE_A:
/* 			RT_ASSERT(false, ("Error wireless a mode\n")); */
		break;
	case WIRELESS_MODE_G:
		regBwOpMode = BW_OPMODE_20MHZ;
		break;
	case WIRELESS_MODE_AUTO:
		regBwOpMode = BW_OPMODE_20MHZ;
		break;
	case WIRELESS_MODE_N_24G:
		/*  It support CCK rate by default. */
		/*  CCK rate will be filtered out only when associated AP does not support it. */
		regBwOpMode = BW_OPMODE_20MHZ;
		break;
	case WIRELESS_MODE_N_5G:
/* 			RT_ASSERT(false, ("Error wireless mode")); */
		regBwOpMode = BW_OPMODE_5G;
		break;

	default: /* for MacOSX compiler warning. */
		break;
	}

	rtw_write8(padapter, REG_BWOPMODE, regBwOpMode);

}