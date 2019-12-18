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
struct brcmf_bus {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {size_t (* get_ramsize ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t brcmf_bus_get_ramsize(struct brcmf_bus *bus)
{
	if (!bus->ops->get_ramsize)
		return 0;

	return bus->ops->get_ramsize(bus->dev);
}