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
typedef  int /*<<< orphan*/  u32 ;
struct rndis_wlan_private {int param_power_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM4320_DEFAULT_TXPOWER_DBM_100 ; 
 int /*<<< orphan*/  BCM4320_DEFAULT_TXPOWER_DBM_25 ; 
 int /*<<< orphan*/  BCM4320_DEFAULT_TXPOWER_DBM_50 ; 
 int /*<<< orphan*/  BCM4320_DEFAULT_TXPOWER_DBM_75 ; 

__attribute__((used)) static u32 get_bcm4320_power_dbm(struct rndis_wlan_private *priv)
{
	switch (priv->param_power_output) {
	default:
	case 3:
		return BCM4320_DEFAULT_TXPOWER_DBM_100;
	case 2:
		return BCM4320_DEFAULT_TXPOWER_DBM_75;
	case 1:
		return BCM4320_DEFAULT_TXPOWER_DBM_50;
	case 0:
		return BCM4320_DEFAULT_TXPOWER_DBM_25;
	}
}