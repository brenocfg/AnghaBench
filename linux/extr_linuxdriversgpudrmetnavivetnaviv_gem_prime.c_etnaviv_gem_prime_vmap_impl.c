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
struct TYPE_4__ {TYPE_1__* import_attach; } ;
struct etnaviv_gem_object {TYPE_2__ base; int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 void* dma_buf_vmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *etnaviv_gem_prime_vmap_impl(struct etnaviv_gem_object *etnaviv_obj)
{
	lockdep_assert_held(&etnaviv_obj->lock);

	return dma_buf_vmap(etnaviv_obj->base.import_attach->dmabuf);
}