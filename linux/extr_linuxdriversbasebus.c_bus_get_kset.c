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
struct kset {int dummy; } ;
struct bus_type {TYPE_1__* p; } ;
struct TYPE_2__ {struct kset subsys; } ;

/* Variables and functions */

struct kset *bus_get_kset(struct bus_type *bus)
{
	return &bus->p->subsys;
}