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
typedef  enum drbd_conns { ____Placeholder_drbd_conns } drbd_conns ;

/* Variables and functions */
 int C_PAUSED_SYNC_T ; 
 int C_SYNC_TARGET ; 

__attribute__((used)) static inline bool is_sync_target_state(enum drbd_conns connection_state)
{
	return	connection_state == C_SYNC_TARGET ||
		connection_state == C_PAUSED_SYNC_T;
}