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
struct be_eth_wrb {scalar_t__ rsvd0; scalar_t__ frag_len; scalar_t__ frag_pa_lo; scalar_t__ frag_pa_hi; } ;

/* Variables and functions */

__attribute__((used)) static inline void wrb_fill_dummy(struct be_eth_wrb *wrb)
{
	wrb->frag_pa_hi = 0;
	wrb->frag_pa_lo = 0;
	wrb->frag_len = 0;
	wrb->rsvd0 = 0;
}