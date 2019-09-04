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

/* Variables and functions */
 int ATC_BTSIZE_MAX ; 
 int ATC_REG_TO_SRC_WIDTH (int) ; 

__attribute__((used)) static inline int atc_calc_bytes_left(int current_len, u32 ctrla)
{
	u32 btsize = (ctrla & ATC_BTSIZE_MAX);
	u32 src_width = ATC_REG_TO_SRC_WIDTH(ctrla);

	/*
	 * According to the datasheet, when reading the Control A Register
	 * (ctrla), the Buffer Transfer Size (btsize) bitfield refers to the
	 * number of transfers completed on the Source Interface.
	 * So btsize is always a number of source width transfers.
	 */
	return current_len - (btsize << src_width);
}