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
typedef  int u16 ;
struct rtllib_device {int dummy; } ;

/* Variables and functions */
 int*** MCS_DATA_RATE ; 

u16  TxCountToDataRate(struct rtllib_device *ieee, u8 nDataRate)
{
	u16	CCKOFDMRate[12] = {0x02, 0x04, 0x0b, 0x16, 0x0c, 0x12, 0x18,
				   0x24, 0x30, 0x48, 0x60, 0x6c};
	u8	is40MHz = 0;
	u8	isShortGI = 0;

	if (nDataRate < 12)
		return CCKOFDMRate[nDataRate];
	if (nDataRate >= 0x10 && nDataRate <= 0x1f) {
		is40MHz = 0;
		isShortGI = 0;
	} else if (nDataRate >= 0x20  && nDataRate <= 0x2f) {
		is40MHz = 1;
		isShortGI = 0;
	} else if (nDataRate >= 0x30  && nDataRate <= 0x3f) {
		is40MHz = 0;
		isShortGI = 1;
	} else if (nDataRate >= 0x40  && nDataRate <= 0x4f) {
		is40MHz = 1;
		isShortGI = 1;
	}
	return MCS_DATA_RATE[is40MHz][isShortGI][nDataRate&0xf];
}