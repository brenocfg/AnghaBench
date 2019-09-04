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
struct ttm_prime_object {int real_type; void (* refcount_release ) (struct ttm_base_object**) ;int /*<<< orphan*/  base; int /*<<< orphan*/ * dma_buf; int /*<<< orphan*/  size; int /*<<< orphan*/  mutex; } ;
struct ttm_object_file {int dummy; } ;
typedef  enum ttm_object_type { ____Placeholder_ttm_object_type } ttm_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (size_t) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ttm_base_object_init (struct ttm_object_file*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct ttm_base_object*,int)) ; 
 int /*<<< orphan*/  ttm_prime_refcount_release ; 
 int /*<<< orphan*/  ttm_prime_type ; 

int ttm_prime_object_init(struct ttm_object_file *tfile, size_t size,
			  struct ttm_prime_object *prime, bool shareable,
			  enum ttm_object_type type,
			  void (*refcount_release) (struct ttm_base_object **),
			  void (*ref_obj_release) (struct ttm_base_object *,
						   enum ttm_ref_type ref_type))
{
	mutex_init(&prime->mutex);
	prime->size = PAGE_ALIGN(size);
	prime->real_type = type;
	prime->dma_buf = NULL;
	prime->refcount_release = refcount_release;
	return ttm_base_object_init(tfile, &prime->base, shareable,
				    ttm_prime_type,
				    ttm_prime_refcount_release,
				    ref_obj_release);
}