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
typedef  int u64 ;

/* Variables and functions */
 int I40E_RXD_QW1_LENGTH_SPH_MASK ; 

__attribute__((used)) static inline bool i40e_rx_is_programming_status(u64 qw)
{
	/* The Rx filter programming status and SPH bit occupy the same
	 * spot in the descriptor. Since we don't support packet split we
	 * can just reuse the bit as an indication that this is a
	 * programming status descriptor.
	 */
	return qw & I40E_RXD_QW1_LENGTH_SPH_MASK;
}