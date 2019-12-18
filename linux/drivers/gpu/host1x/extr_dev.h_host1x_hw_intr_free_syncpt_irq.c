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
struct host1x {TYPE_1__* intr_op; } ;
struct TYPE_2__ {int (* free_syncpt_irq ) (struct host1x*) ;} ;

/* Variables and functions */
 int stub1 (struct host1x*) ; 

__attribute__((used)) static inline int host1x_hw_intr_free_syncpt_irq(struct host1x *host)
{
	return host->intr_op->free_syncpt_irq(host);
}