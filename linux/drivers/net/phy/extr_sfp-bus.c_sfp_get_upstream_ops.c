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
struct sfp_upstream_ops {int dummy; } ;
struct sfp_bus {struct sfp_upstream_ops const* upstream_ops; scalar_t__ registered; } ;

/* Variables and functions */

__attribute__((used)) static const struct sfp_upstream_ops *sfp_get_upstream_ops(struct sfp_bus *bus)
{
	return bus->registered ? bus->upstream_ops : NULL;
}