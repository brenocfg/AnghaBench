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
struct vnt_private {int rf_type; } ;

/* Variables and functions */
#define  RF_AIROHA7230 133 
#define  RF_AL2230 132 
#define  RF_AL2230S 131 
#define  RF_VT3226 130 
#define  RF_VT3226D0 129 
#define  RF_VT3342A0 128 

void vnt_rf_rssi_to_dbm(struct vnt_private *priv, u8 rssi, long *dbm)
{
	u8 idx = ((rssi & 0xc0) >> 6) & 0x03;
	long b = rssi & 0x3f;
	long a = 0;
	u8 airoharf[4] = {0, 18, 0, 40};

	switch (priv->rf_type) {
	case RF_AL2230:
	case RF_AL2230S:
	case RF_AIROHA7230:
	case RF_VT3226:
	case RF_VT3226D0:
	case RF_VT3342A0:
		a = airoharf[idx];
		break;
	default:
		break;
	}

	*dbm = -1 * (a + b * 2);
}