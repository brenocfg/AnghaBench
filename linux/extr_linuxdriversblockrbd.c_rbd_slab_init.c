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

/* Variables and functions */
 int ENOMEM ; 
 void* KMEM_CACHE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int) ; 
 int /*<<< orphan*/  rbd_img_request ; 
 int /*<<< orphan*/ * rbd_img_request_cache ; 
 int /*<<< orphan*/  rbd_obj_request ; 
 void* rbd_obj_request_cache ; 

__attribute__((used)) static int rbd_slab_init(void)
{
	rbd_assert(!rbd_img_request_cache);
	rbd_img_request_cache = KMEM_CACHE(rbd_img_request, 0);
	if (!rbd_img_request_cache)
		return -ENOMEM;

	rbd_assert(!rbd_obj_request_cache);
	rbd_obj_request_cache = KMEM_CACHE(rbd_obj_request, 0);
	if (!rbd_obj_request_cache)
		goto out_err;

	return 0;

out_err:
	kmem_cache_destroy(rbd_img_request_cache);
	rbd_img_request_cache = NULL;
	return -ENOMEM;
}