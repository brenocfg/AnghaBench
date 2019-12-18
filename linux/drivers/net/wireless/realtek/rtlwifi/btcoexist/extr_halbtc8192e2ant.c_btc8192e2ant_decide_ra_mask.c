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
typedef  int u32 ;
struct btc_coexist {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 btc8192e2ant_decide_ra_mask(struct btc_coexist *btcoexist,
				       u8 ss_type, u32 ra_mask_type)
{
	u32 dis_ra_mask = 0x0;

	switch (ra_mask_type) {
	case 0: /* normal mode */
		if (ss_type == 2)
			dis_ra_mask = 0x0; /* enable 2ss */
		else
			dis_ra_mask = 0xfff00000; /* disable 2ss */
		break;
	case 1: /* disable cck 1/2 */
		if (ss_type == 2)
			dis_ra_mask = 0x00000003; /* enable 2ss */
		else
			dis_ra_mask = 0xfff00003; /* disable 2ss */
		break;
	case 2: /* disable cck 1/2/5.5, ofdm 6/9/12/18/24, mcs 0/1/2/3/4 */
		if (ss_type == 2)
			dis_ra_mask = 0x0001f1f7; /* enable 2ss */
		else
			dis_ra_mask = 0xfff1f1f7; /* disable 2ss */
		break;
	default:
		break;
	}

	return dis_ra_mask;
}