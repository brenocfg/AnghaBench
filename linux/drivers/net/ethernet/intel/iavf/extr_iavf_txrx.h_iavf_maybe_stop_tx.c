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
struct iavf_ring {int dummy; } ;

/* Variables and functions */
 int IAVF_DESC_UNUSED (struct iavf_ring*) ; 
 int __iavf_maybe_stop_tx (struct iavf_ring*,int) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int iavf_maybe_stop_tx(struct iavf_ring *tx_ring, int size)
{
	if (likely(IAVF_DESC_UNUSED(tx_ring) >= size))
		return 0;
	return __iavf_maybe_stop_tx(tx_ring, size);
}