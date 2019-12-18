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
struct etnaviv_gem_object {int /*<<< orphan*/  sgt; TYPE_2__ base; scalar_t__ pages; scalar_t__ vaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  dmabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_buf_vunmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  drm_prime_gem_destroy (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (scalar_t__) ; 

__attribute__((used)) static void etnaviv_gem_prime_release(struct etnaviv_gem_object *etnaviv_obj)
{
	if (etnaviv_obj->vaddr)
		dma_buf_vunmap(etnaviv_obj->base.import_attach->dmabuf,
			       etnaviv_obj->vaddr);

	/* Don't drop the pages for imported dmabuf, as they are not
	 * ours, just free the array we allocated:
	 */
	if (etnaviv_obj->pages)
		kvfree(etnaviv_obj->pages);

	drm_prime_gem_destroy(&etnaviv_obj->base, etnaviv_obj->sgt);
}