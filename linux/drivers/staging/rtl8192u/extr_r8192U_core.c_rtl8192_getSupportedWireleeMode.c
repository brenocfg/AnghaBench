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
struct r8192_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  RF_8225 131 
#define  RF_8256 130 
#define  RF_8258 129 
#define  RF_PSEUDO_11N 128 
 int WIRELESS_MODE_A ; 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 int WIRELESS_MODE_N_24G ; 
 int WIRELESS_MODE_N_5G ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static u8 rtl8192_getSupportedWireleeMode(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8 ret = 0;

	switch (priv->rf_chip) {
	case RF_8225:
	case RF_8256:
	case RF_PSEUDO_11N:
		ret = WIRELESS_MODE_N_24G | WIRELESS_MODE_G | WIRELESS_MODE_B;
		break;
	case RF_8258:
		ret = WIRELESS_MODE_A | WIRELESS_MODE_N_5G;
		break;
	default:
		ret = WIRELESS_MODE_B;
		break;
	}
	return ret;
}