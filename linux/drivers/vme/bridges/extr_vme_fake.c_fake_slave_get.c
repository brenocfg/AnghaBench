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
struct vme_slave_resource {unsigned int number; int /*<<< orphan*/  mtx; TYPE_1__* parent; } ;
struct fake_driver {TYPE_2__* slaves; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int enabled; unsigned long long vme_base; unsigned long long size; int /*<<< orphan*/  cycle; int /*<<< orphan*/  aspace; int /*<<< orphan*/  buf_base; } ;
struct TYPE_3__ {struct fake_driver* driver_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  fake_ptr_to_pci (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fake_slave_get(struct vme_slave_resource *image, int *enabled,
		unsigned long long *vme_base, unsigned long long *size,
		dma_addr_t *buf_base, u32 *aspace, u32 *cycle)
{
	unsigned int i;
	struct fake_driver *bridge;

	bridge = image->parent->driver_priv;

	i = image->number;

	mutex_lock(&image->mtx);

	*enabled = bridge->slaves[i].enabled;
	*vme_base = bridge->slaves[i].vme_base;
	*size = bridge->slaves[i].size;
	*buf_base = fake_ptr_to_pci(bridge->slaves[i].buf_base);
	*aspace = bridge->slaves[i].aspace;
	*cycle = bridge->slaves[i].cycle;

	mutex_unlock(&image->mtx);

	return 0;
}