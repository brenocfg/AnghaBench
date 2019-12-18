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
typedef  int /*<<< orphan*/  u32 ;
struct vme_master_resource {unsigned int number; TYPE_1__* parent; } ;
struct fake_driver {TYPE_2__* masters; } ;
struct TYPE_4__ {int enabled; unsigned long long vme_base; unsigned long long size; int /*<<< orphan*/  dwidth; int /*<<< orphan*/  cycle; int /*<<< orphan*/  aspace; } ;
struct TYPE_3__ {struct fake_driver* driver_priv; } ;

/* Variables and functions */

__attribute__((used)) static int __fake_master_get(struct vme_master_resource *image, int *enabled,
		unsigned long long *vme_base, unsigned long long *size,
		u32 *aspace, u32 *cycle, u32 *dwidth)
{
	unsigned int i;
	struct fake_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	*enabled = bridge->masters[i].enabled;
	*vme_base = bridge->masters[i].vme_base;
	*size = bridge->masters[i].size;
	*aspace = bridge->masters[i].aspace;
	*cycle = bridge->masters[i].cycle;
	*dwidth = bridge->masters[i].dwidth;

	return 0;
}