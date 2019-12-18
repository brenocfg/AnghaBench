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
typedef  int /*<<< orphan*/  u16 ;
struct mt7601u_rxwi {int /*<<< orphan*/  freq_off; } ;
struct mt7601u_dev {int /*<<< orphan*/  avg_rssi; int /*<<< orphan*/  bcn_phy_mode; int /*<<< orphan*/  bcn_freq_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_RXWI_RATE_PHY ; 
 int /*<<< orphan*/  ewma_rssi_add (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
mt7601u_rx_monitor_beacon(struct mt7601u_dev *dev, struct mt7601u_rxwi *rxwi,
			  u16 rate, int rssi)
{
	dev->bcn_freq_off = rxwi->freq_off;
	dev->bcn_phy_mode = FIELD_GET(MT_RXWI_RATE_PHY, rate);
	ewma_rssi_add(&dev->avg_rssi, -rssi);
}