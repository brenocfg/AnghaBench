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
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rbd_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rbd_img_request_cache ; 
 int /*<<< orphan*/ * rbd_obj_request_cache ; 

__attribute__((used)) static void rbd_slab_exit(void)
{
	rbd_assert(rbd_obj_request_cache);
	kmem_cache_destroy(rbd_obj_request_cache);
	rbd_obj_request_cache = NULL;

	rbd_assert(rbd_img_request_cache);
	kmem_cache_destroy(rbd_img_request_cache);
	rbd_img_request_cache = NULL;
}