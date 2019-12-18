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
struct sxgbe_rx_ctxt_desc {int tstamp_lo; scalar_t__ tstamp_hi; } ;

/* Variables and functions */

__attribute__((used)) static u64 sxgbe_get_rx_timestamp(struct sxgbe_rx_ctxt_desc *p)
{
	u64 ns;

	ns = p->tstamp_lo;
	ns |= ((u64)p->tstamp_hi) << 32;

	return ns;
}