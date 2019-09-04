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

/* Variables and functions */
 int OCRDMA_STATE_FLAG_ENABLED ; 
 int OCRDMA_STATE_FLAG_SYNC ; 

__attribute__((used)) static inline u8 ocrdma_is_enabled_and_synced(u32 state)
{	/* May also be used to interpret TC-state, QCN-state
	 * Appl-state and Logical-link-state in future.
	 */
	return (state & OCRDMA_STATE_FLAG_ENABLED) &&
		(state & OCRDMA_STATE_FLAG_SYNC);
}