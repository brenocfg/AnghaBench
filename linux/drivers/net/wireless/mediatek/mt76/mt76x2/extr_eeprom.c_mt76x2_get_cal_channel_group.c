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
typedef  enum mt76x2_cal_channel_group { ____Placeholder_mt76x2_cal_channel_group } mt76x2_cal_channel_group ;

/* Variables and functions */
 int MT_CH_5G_JAPAN ; 
 int MT_CH_5G_UNII_1 ; 
 int MT_CH_5G_UNII_2 ; 
 int MT_CH_5G_UNII_2E_1 ; 
 int MT_CH_5G_UNII_2E_2 ; 
 int MT_CH_5G_UNII_3 ; 

__attribute__((used)) static enum mt76x2_cal_channel_group
mt76x2_get_cal_channel_group(int channel)
{
	if (channel >= 184 && channel <= 196)
		return MT_CH_5G_JAPAN;
	if (channel <= 48)
		return MT_CH_5G_UNII_1;
	if (channel <= 64)
		return MT_CH_5G_UNII_2;
	if (channel <= 114)
		return MT_CH_5G_UNII_2E_1;
	if (channel <= 144)
		return MT_CH_5G_UNII_2E_2;
	return MT_CH_5G_UNII_3;
}