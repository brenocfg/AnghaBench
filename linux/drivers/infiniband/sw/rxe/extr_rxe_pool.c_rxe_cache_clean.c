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
struct rxe_type_info {int flags; int /*<<< orphan*/ * cache; } ;

/* Variables and functions */
 int RXE_POOL_NO_ALLOC ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 struct rxe_type_info* rxe_type_info ; 

__attribute__((used)) static void rxe_cache_clean(size_t cnt)
{
	int i;
	struct rxe_type_info *type;

	for (i = 0; i < cnt; i++) {
		type = &rxe_type_info[i];
		if (!(type->flags & RXE_POOL_NO_ALLOC)) {
			kmem_cache_destroy(type->cache);
			type->cache = NULL;
		}
	}
}