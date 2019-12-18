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
struct ni_gpct {TYPE_1__* counter_dev; } ;
typedef  enum ni_gpct_register { ____Placeholder_ni_gpct_register } ni_gpct_register ;
struct TYPE_2__ {unsigned int (* read ) (struct ni_gpct*,int) ;} ;

/* Variables and functions */
 int NITIO_NUM_REGS ; 
 unsigned int stub1 (struct ni_gpct*,int) ; 

unsigned int ni_tio_read(struct ni_gpct *counter, enum ni_gpct_register reg)
{
	if (reg < NITIO_NUM_REGS)
		return counter->counter_dev->read(counter, reg);
	return 0;
}