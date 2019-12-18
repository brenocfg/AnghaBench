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
typedef  enum comm_dir { ____Placeholder_comm_dir } comm_dir ;

/* Variables and functions */
 int COMM_DIR_RX ; 
 int RX_SYNC_SHIFT_BASE ; 
 int TX_SYNC_SHIFT_BASE ; 

__attribute__((used)) static u32 ucc_get_tdm_sync_shift(enum comm_dir mode, u32 tdm_num)
{
	u32 shift;

	shift = (mode == COMM_DIR_RX) ? RX_SYNC_SHIFT_BASE : TX_SYNC_SHIFT_BASE;
	shift -= tdm_num * 2;

	return shift;
}