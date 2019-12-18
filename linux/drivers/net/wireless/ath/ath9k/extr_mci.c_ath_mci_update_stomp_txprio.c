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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 size_t ATH_BTCOEX_STOMP_ALL ; 
 size_t ATH_BTCOEX_STOMP_LOW ; 
 size_t ATH_BTCOEX_STOMP_NONE ; 
 scalar_t__ ATH_MCI_HI_PRIO ; 

__attribute__((used)) static void ath_mci_update_stomp_txprio(u8 cur_txprio, u8 *stomp_prio)
{
	if (cur_txprio < stomp_prio[ATH_BTCOEX_STOMP_NONE])
		stomp_prio[ATH_BTCOEX_STOMP_NONE] = cur_txprio;

	if (cur_txprio > stomp_prio[ATH_BTCOEX_STOMP_ALL])
		stomp_prio[ATH_BTCOEX_STOMP_ALL] = cur_txprio;

	if ((cur_txprio > ATH_MCI_HI_PRIO) &&
	    (cur_txprio < stomp_prio[ATH_BTCOEX_STOMP_LOW]))
		stomp_prio[ATH_BTCOEX_STOMP_LOW] = cur_txprio;
}