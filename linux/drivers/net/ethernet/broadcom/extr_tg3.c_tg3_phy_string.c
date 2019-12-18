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
struct tg3 {int phy_id; } ;

/* Variables and functions */
#define  TG3_PHY_ID_BCM5400 151 
#define  TG3_PHY_ID_BCM5401 150 
#define  TG3_PHY_ID_BCM5411 149 
#define  TG3_PHY_ID_BCM5701 148 
#define  TG3_PHY_ID_BCM5703 147 
#define  TG3_PHY_ID_BCM5704 146 
#define  TG3_PHY_ID_BCM5705 145 
#define  TG3_PHY_ID_BCM5714 144 
#define  TG3_PHY_ID_BCM5718C 143 
#define  TG3_PHY_ID_BCM5718S 142 
#define  TG3_PHY_ID_BCM5719C 141 
#define  TG3_PHY_ID_BCM5720C 140 
#define  TG3_PHY_ID_BCM5750 139 
#define  TG3_PHY_ID_BCM5752 138 
#define  TG3_PHY_ID_BCM5755 137 
#define  TG3_PHY_ID_BCM5756 136 
#define  TG3_PHY_ID_BCM5761 135 
#define  TG3_PHY_ID_BCM5762 134 
#define  TG3_PHY_ID_BCM57765 133 
#define  TG3_PHY_ID_BCM5780 132 
#define  TG3_PHY_ID_BCM5784 131 
#define  TG3_PHY_ID_BCM5787 130 
#define  TG3_PHY_ID_BCM5906 129 
#define  TG3_PHY_ID_BCM8002 128 
 int TG3_PHY_ID_MASK ; 

__attribute__((used)) static char *tg3_phy_string(struct tg3 *tp)
{
	switch (tp->phy_id & TG3_PHY_ID_MASK) {
	case TG3_PHY_ID_BCM5400:	return "5400";
	case TG3_PHY_ID_BCM5401:	return "5401";
	case TG3_PHY_ID_BCM5411:	return "5411";
	case TG3_PHY_ID_BCM5701:	return "5701";
	case TG3_PHY_ID_BCM5703:	return "5703";
	case TG3_PHY_ID_BCM5704:	return "5704";
	case TG3_PHY_ID_BCM5705:	return "5705";
	case TG3_PHY_ID_BCM5750:	return "5750";
	case TG3_PHY_ID_BCM5752:	return "5752";
	case TG3_PHY_ID_BCM5714:	return "5714";
	case TG3_PHY_ID_BCM5780:	return "5780";
	case TG3_PHY_ID_BCM5755:	return "5755";
	case TG3_PHY_ID_BCM5787:	return "5787";
	case TG3_PHY_ID_BCM5784:	return "5784";
	case TG3_PHY_ID_BCM5756:	return "5722/5756";
	case TG3_PHY_ID_BCM5906:	return "5906";
	case TG3_PHY_ID_BCM5761:	return "5761";
	case TG3_PHY_ID_BCM5718C:	return "5718C";
	case TG3_PHY_ID_BCM5718S:	return "5718S";
	case TG3_PHY_ID_BCM57765:	return "57765";
	case TG3_PHY_ID_BCM5719C:	return "5719C";
	case TG3_PHY_ID_BCM5720C:	return "5720C";
	case TG3_PHY_ID_BCM5762:	return "5762C";
	case TG3_PHY_ID_BCM8002:	return "8002/serdes";
	case 0:			return "serdes";
	default:		return "unknown";
	}
}