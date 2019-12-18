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
typedef  int u16 ;
struct rtw_sec_desc {int default_key_search; } ;
struct rtw_dev {struct rtw_sec_desc sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_CR ; 
 int /*<<< orphan*/  RTW_SEC_CONFIG ; 
 int RTW_SEC_ENGINE_EN ; 
 int RTW_SEC_RX_BC_USE_DK ; 
 int RTW_SEC_RX_DEC_EN ; 
 int RTW_SEC_RX_UNI_USE_DK ; 
 int RTW_SEC_TX_BC_USE_DK ; 
 int RTW_SEC_TX_DEC_EN ; 
 int RTW_SEC_TX_UNI_USE_DK ; 
 int rtw_read16 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_write16 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 

void rtw_sec_enable_sec_engine(struct rtw_dev *rtwdev)
{
	struct rtw_sec_desc *sec = &rtwdev->sec;
	u16 ctrl_reg;
	u16 sec_config;

	/* default use default key search for now */
	sec->default_key_search = true;

	ctrl_reg = rtw_read16(rtwdev, REG_CR);
	ctrl_reg |= RTW_SEC_ENGINE_EN;
	rtw_write16(rtwdev, REG_CR, ctrl_reg);

	sec_config = rtw_read16(rtwdev, RTW_SEC_CONFIG);

	sec_config |= RTW_SEC_TX_DEC_EN | RTW_SEC_RX_DEC_EN;
	if (sec->default_key_search)
		sec_config |= RTW_SEC_TX_UNI_USE_DK | RTW_SEC_RX_UNI_USE_DK |
			      RTW_SEC_TX_BC_USE_DK | RTW_SEC_RX_BC_USE_DK;

	rtw_write16(rtwdev, RTW_SEC_CONFIG, sec_config);
}