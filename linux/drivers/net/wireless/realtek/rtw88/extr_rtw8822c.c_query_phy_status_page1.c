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
struct rtw_rx_pkt_stat {scalar_t__ rate; int bw; scalar_t__* rx_power; int /*<<< orphan*/  signal_power; int /*<<< orphan*/  rssi; } ;
struct rtw_dev {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ DESC_RATE11M ; 
 scalar_t__ DESC_RATEMCS0 ; 
 int GET_PHY_STAT_P1_HT_RXSC (int*) ; 
 int GET_PHY_STAT_P1_L_RXSC (int*) ; 
 scalar_t__ GET_PHY_STAT_P1_PWDB_A (int*) ; 
 scalar_t__ GET_PHY_STAT_P1_PWDB_B (int*) ; 
 size_t RF_PATH_A ; 
 size_t RF_PATH_B ; 
 int RTW_CHANNEL_WIDTH_20 ; 
 int RTW_CHANNEL_WIDTH_40 ; 
 int RTW_CHANNEL_WIDTH_80 ; 
 int /*<<< orphan*/  max3 (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  rtw_phy_rf_power_2_rssi (scalar_t__*,int) ; 

__attribute__((used)) static void query_phy_status_page1(struct rtw_dev *rtwdev, u8 *phy_status,
				   struct rtw_rx_pkt_stat *pkt_stat)
{
	u8 rxsc, bw;
	s8 min_rx_power = -120;

	if (pkt_stat->rate > DESC_RATE11M && pkt_stat->rate < DESC_RATEMCS0)
		rxsc = GET_PHY_STAT_P1_L_RXSC(phy_status);
	else
		rxsc = GET_PHY_STAT_P1_HT_RXSC(phy_status);

	if (rxsc >= 9 && rxsc <= 12)
		bw = RTW_CHANNEL_WIDTH_40;
	else if (rxsc >= 13)
		bw = RTW_CHANNEL_WIDTH_80;
	else
		bw = RTW_CHANNEL_WIDTH_20;

	pkt_stat->rx_power[RF_PATH_A] = GET_PHY_STAT_P1_PWDB_A(phy_status) - 110;
	pkt_stat->rx_power[RF_PATH_B] = GET_PHY_STAT_P1_PWDB_B(phy_status) - 110;
	pkt_stat->rssi = rtw_phy_rf_power_2_rssi(pkt_stat->rx_power, 2);
	pkt_stat->bw = bw;
	pkt_stat->signal_power = max3(pkt_stat->rx_power[RF_PATH_A],
				      pkt_stat->rx_power[RF_PATH_B],
				      min_rx_power);
}