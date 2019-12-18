#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_subdevice {TYPE_2__* range_table; } ;
struct TYPE_4__ {TYPE_1__* range; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int RF_EXTERNAL ; 

__attribute__((used)) static inline bool comedi_range_is_external(struct comedi_subdevice *s,
					    unsigned int range)
{
	return !!(s->range_table->range[range].flags & RF_EXTERNAL);
}