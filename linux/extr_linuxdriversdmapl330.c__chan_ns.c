#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int irq_ns; } ;
struct pl330_dmac {TYPE_1__ pcfg; } ;

/* Variables and functions */

__attribute__((used)) static bool _chan_ns(const struct pl330_dmac *pl330, int i)
{
	return pl330->pcfg.irq_ns & (1 << i);
}