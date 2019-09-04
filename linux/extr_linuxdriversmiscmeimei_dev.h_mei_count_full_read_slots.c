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
struct mei_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* rdbuf_full_slots ) (struct mei_device*) ;} ;

/* Variables and functions */
 int stub1 (struct mei_device*) ; 

__attribute__((used)) static inline int mei_count_full_read_slots(struct mei_device *dev)
{
	return dev->ops->rdbuf_full_slots(dev);
}