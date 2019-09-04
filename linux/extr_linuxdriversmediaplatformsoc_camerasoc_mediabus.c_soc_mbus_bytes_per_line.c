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
typedef  int u32 ;
struct soc_mbus_pixelfmt {scalar_t__ layout; int bits_per_sample; int packing; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ SOC_MBUS_LAYOUT_PACKED ; 
#define  SOC_MBUS_PACKING_1_5X8 134 
#define  SOC_MBUS_PACKING_2X8_PADHI 133 
#define  SOC_MBUS_PACKING_2X8_PADLO 132 
#define  SOC_MBUS_PACKING_EXTEND16 131 
#define  SOC_MBUS_PACKING_EXTEND32 130 
#define  SOC_MBUS_PACKING_NONE 129 
#define  SOC_MBUS_PACKING_VARIABLE 128 

s32 soc_mbus_bytes_per_line(u32 width, const struct soc_mbus_pixelfmt *mf)
{
	if (mf->layout != SOC_MBUS_LAYOUT_PACKED)
		return width * mf->bits_per_sample / 8;

	switch (mf->packing) {
	case SOC_MBUS_PACKING_NONE:
		return width * mf->bits_per_sample / 8;
	case SOC_MBUS_PACKING_2X8_PADHI:
	case SOC_MBUS_PACKING_2X8_PADLO:
	case SOC_MBUS_PACKING_EXTEND16:
		return width * 2;
	case SOC_MBUS_PACKING_1_5X8:
		return width * 3 / 2;
	case SOC_MBUS_PACKING_VARIABLE:
		return 0;
	case SOC_MBUS_PACKING_EXTEND32:
		return width * 4;
	}
	return -EINVAL;
}