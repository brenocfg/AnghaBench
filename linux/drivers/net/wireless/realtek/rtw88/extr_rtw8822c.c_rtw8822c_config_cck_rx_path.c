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
typedef  scalar_t__ u8 ;
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ BB_PATH_A ; 
 scalar_t__ BB_PATH_AB ; 
 scalar_t__ BB_PATH_B ; 
 int /*<<< orphan*/  REG_CCANRX ; 
 int /*<<< orphan*/  REG_RXCCKSEL ; 
 int /*<<< orphan*/  rtw_write32_mask (struct rtw_dev*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void rtw8822c_config_cck_rx_path(struct rtw_dev *rtwdev, u8 rx_path)
{
	if (rx_path == BB_PATH_A || rx_path == BB_PATH_B) {
		rtw_write32_mask(rtwdev, REG_CCANRX, 0x00060000, 0x0);
		rtw_write32_mask(rtwdev, REG_CCANRX, 0x00600000, 0x0);
	} else if (rx_path == BB_PATH_AB) {
		rtw_write32_mask(rtwdev, REG_CCANRX, 0x00600000, 0x1);
		rtw_write32_mask(rtwdev, REG_CCANRX, 0x00060000, 0x1);
	}

	if (rx_path == BB_PATH_A)
		rtw_write32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x0);
	else if (rx_path == BB_PATH_B)
		rtw_write32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x5);
	else if (rx_path == BB_PATH_AB)
		rtw_write32_mask(rtwdev, REG_RXCCKSEL, 0x0f000000, 0x1);
}