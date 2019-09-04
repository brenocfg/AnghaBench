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
struct ace_private {int dummy; } ;

/* Variables and functions */
 int ACE_TX_RING_ENTRIES (struct ace_private*) ; 

__attribute__((used)) static inline int tx_space (struct ace_private *ap, u32 csm, u32 prd)
{
	return (csm - prd - 1) & (ACE_TX_RING_ENTRIES(ap) - 1);
}