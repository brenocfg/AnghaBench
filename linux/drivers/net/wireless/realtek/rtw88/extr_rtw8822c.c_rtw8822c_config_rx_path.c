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
struct rtw_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtw8822c_config_cck_rx_path (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw8822c_config_ofdm_rx_path (struct rtw_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtw8822c_config_rx_path(struct rtw_dev *rtwdev, u8 rx_path)
{
	rtw8822c_config_cck_rx_path(rtwdev, rx_path);
	rtw8822c_config_ofdm_rx_path(rtwdev, rx_path);
}