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
 scalar_t__ R1_CURRENT_STATE (int) ; 
 int R1_READY_FOR_DATA ; 
 scalar_t__ R1_STATE_TRAN ; 

__attribute__((used)) static inline bool mmc_blk_in_tran_state(u32 status)
{
	/*
	 * Some cards mishandle the status bits, so make sure to check both the
	 * busy indication and the card state.
	 */
	return status & R1_READY_FOR_DATA &&
	       (R1_CURRENT_STATE(status) == R1_STATE_TRAN);
}