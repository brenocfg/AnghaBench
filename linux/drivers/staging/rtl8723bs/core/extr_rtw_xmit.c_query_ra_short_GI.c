#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int sgi_20m; int sgi_40m; } ;
struct sta_info {int bw_mode; TYPE_1__ htpriv; } ;

/* Variables and functions */
#define  CHANNEL_WIDTH_20 130 
#define  CHANNEL_WIDTH_40 129 
#define  CHANNEL_WIDTH_80 128 

u8 query_ra_short_GI(struct sta_info *psta)
{
	u8 sgi = false, sgi_20m = false, sgi_40m = false, sgi_80m = false;

	sgi_20m = psta->htpriv.sgi_20m;
	sgi_40m = psta->htpriv.sgi_40m;

	switch (psta->bw_mode) {
	case CHANNEL_WIDTH_80:
		sgi = sgi_80m;
		break;
	case CHANNEL_WIDTH_40:
		sgi = sgi_40m;
		break;
	case CHANNEL_WIDTH_20:
	default:
		sgi = sgi_20m;
		break;
	}

	return sgi;
}