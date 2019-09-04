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
struct tx_desc {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void wr_gen2(struct tx_desc *d, unsigned int gen)
{
#if SGE_NUM_GENBITS == 2
	d->flit[TX_DESC_FLITS - 1] = cpu_to_be64(gen);
#endif
}