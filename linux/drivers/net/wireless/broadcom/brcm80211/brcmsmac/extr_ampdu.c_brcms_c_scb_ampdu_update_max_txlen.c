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
typedef  size_t u8 ;
typedef  size_t u32 ;
struct ampdu_info {size_t*** max_txlen; } ;

/* Variables and functions */
 size_t MCS_TABLE_SIZE ; 
 size_t mcs_2_rate (size_t,int,int) ; 

__attribute__((used)) static void brcms_c_scb_ampdu_update_max_txlen(struct ampdu_info *ampdu, u8 dur)
{
	u32 rate, mcs;

	for (mcs = 0; mcs < MCS_TABLE_SIZE; mcs++) {
		/* rate is in Kbps; dur is in msec ==> len = (rate * dur) / 8 */
		/* 20MHz, No SGI */
		rate = mcs_2_rate(mcs, false, false);
		ampdu->max_txlen[mcs][0][0] = (rate * dur) >> 3;
		/* 40 MHz, No SGI */
		rate = mcs_2_rate(mcs, true, false);
		ampdu->max_txlen[mcs][1][0] = (rate * dur) >> 3;
		/* 20MHz, SGI */
		rate = mcs_2_rate(mcs, false, true);
		ampdu->max_txlen[mcs][0][1] = (rate * dur) >> 3;
		/* 40 MHz, SGI */
		rate = mcs_2_rate(mcs, true, true);
		ampdu->max_txlen[mcs][1][1] = (rate * dur) >> 3;
	}
}