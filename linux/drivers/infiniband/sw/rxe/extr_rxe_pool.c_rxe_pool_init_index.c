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
typedef  scalar_t__ u32 ;
struct rxe_pool {scalar_t__ max_elem; size_t table_size; int /*<<< orphan*/  table; scalar_t__ min_index; scalar_t__ max_index; } ;

/* Variables and functions */
 int BITS_TO_LONGS (scalar_t__) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int rxe_pool_init_index(struct rxe_pool *pool, u32 max, u32 min)
{
	int err = 0;
	size_t size;

	if ((max - min + 1) < pool->max_elem) {
		pr_warn("not enough indices for max_elem\n");
		err = -EINVAL;
		goto out;
	}

	pool->max_index = max;
	pool->min_index = min;

	size = BITS_TO_LONGS(max - min + 1) * sizeof(long);
	pool->table = kmalloc(size, GFP_KERNEL);
	if (!pool->table) {
		err = -ENOMEM;
		goto out;
	}

	pool->table_size = size;
	bitmap_zero(pool->table, max - min + 1);

out:
	return err;
}