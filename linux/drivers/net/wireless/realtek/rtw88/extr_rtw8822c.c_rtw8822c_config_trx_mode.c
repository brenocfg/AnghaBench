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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int BB_PATH_A ; 
 int BB_PATH_B ; 
 int /*<<< orphan*/  MASK20BITS ; 
 int /*<<< orphan*/  REG_ORITXCODE ; 
 int /*<<< orphan*/  REG_ORITXCODE2 ; 
 int /*<<< orphan*/  rtw8822c_config_rx_path (struct rtw_dev*,int) ; 
 int /*<<< orphan*/  rtw8822c_config_tx_path (struct rtw_dev*,int,int) ; 
 int /*<<< orphan*/  rtw8822c_toggle_igi (struct rtw_dev*) ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rtw8822c_config_trx_mode(struct rtw_dev *rtwdev, u8 tx_path,
				     u8 rx_path, bool is_tx2_path)
{
	if ((tx_path | rx_path) & BB_PATH_A)
		rtw_write32_mask(rtwdev, REG_ORITXCODE, MASK20BITS, 0x33312);
	else
		rtw_write32_mask(rtwdev, REG_ORITXCODE, MASK20BITS, 0x11111);
	if ((tx_path | rx_path) & BB_PATH_B)
		rtw_write32_mask(rtwdev, REG_ORITXCODE2, MASK20BITS, 0x33312);
	else
		rtw_write32_mask(rtwdev, REG_ORITXCODE2, MASK20BITS, 0x11111);

	rtw8822c_config_rx_path(rtwdev, rx_path);
	rtw8822c_config_tx_path(rtwdev, tx_path, is_tx2_path);

	rtw8822c_toggle_igi(rtwdev);
}