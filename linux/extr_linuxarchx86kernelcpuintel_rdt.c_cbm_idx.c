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
struct TYPE_2__ {unsigned int cbm_idx_mult; unsigned int cbm_idx_offset; } ;
struct rdt_resource {TYPE_1__ cache; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int cbm_idx(struct rdt_resource *r, unsigned int closid)
{
	return closid * r->cache.cbm_idx_mult + r->cache.cbm_idx_offset;
}