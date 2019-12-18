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
struct vnt_private {int byRFType; } ;

/* Variables and functions */
#define  RF_AIROHA 130 
#define  RF_AIROHA7230 129 
#define  RF_AL2230S 128 

void
RFvRSSITodBm(struct vnt_private *priv, unsigned char byCurrRSSI, long *pldBm)
{
	unsigned char byIdx = (((byCurrRSSI & 0xC0) >> 6) & 0x03);
	long b = (byCurrRSSI & 0x3F);
	long a = 0;
	unsigned char abyAIROHARF[4] = {0, 18, 0, 40};

	switch (priv->byRFType) {
	case RF_AIROHA:
	case RF_AL2230S:
	case RF_AIROHA7230:
		a = abyAIROHARF[byIdx];
		break;
	default:
		break;
	}

	*pldBm = -1 * (a + b * 2);
}