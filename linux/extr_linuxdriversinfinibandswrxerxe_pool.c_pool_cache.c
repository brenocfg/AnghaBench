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
struct rxe_pool {size_t type; } ;
struct kmem_cache {int dummy; } ;
struct TYPE_2__ {struct kmem_cache* cache; } ;

/* Variables and functions */
 TYPE_1__* rxe_type_info ; 

__attribute__((used)) static inline struct kmem_cache *pool_cache(struct rxe_pool *pool)
{
	return rxe_type_info[pool->type].cache;
}