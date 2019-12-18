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
struct rxe_type_info {int flags; int /*<<< orphan*/  name; int /*<<< orphan*/  cache; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 size_t ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int RXE_NUM_TYPES ; 
 int /*<<< orphan*/  RXE_POOL_ALIGN ; 
 int /*<<< orphan*/  RXE_POOL_CACHE_FLAGS ; 
 int RXE_POOL_NO_ALLOC ; 
 int /*<<< orphan*/  kmem_cache_create (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_cache_clean (int) ; 
 struct rxe_type_info* rxe_type_info ; 

int rxe_cache_init(void)
{
	int err;
	int i;
	size_t size;
	struct rxe_type_info *type;

	for (i = 0; i < RXE_NUM_TYPES; i++) {
		type = &rxe_type_info[i];
		size = ALIGN(type->size, RXE_POOL_ALIGN);
		if (!(type->flags & RXE_POOL_NO_ALLOC)) {
			type->cache =
				kmem_cache_create(type->name, size,
						  RXE_POOL_ALIGN,
						  RXE_POOL_CACHE_FLAGS, NULL);
			if (!type->cache) {
				pr_err("Unable to init kmem cache for %s\n",
				       type->name);
				err = -ENOMEM;
				goto err1;
			}
		}
	}

	return 0;

err1:
	rxe_cache_clean(i);

	return err;
}