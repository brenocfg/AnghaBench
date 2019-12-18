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
struct rxe_pool {int type; unsigned int max_elem; int flags; int /*<<< orphan*/  state; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key_offset; int /*<<< orphan*/  pool_lock; int /*<<< orphan*/  ref_cnt; int /*<<< orphan*/  num_elem; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  tree; int /*<<< orphan*/  elem_size; struct rxe_dev* rxe; } ;
struct rxe_dev {int dummy; } ;
typedef  enum rxe_elem_type { ____Placeholder_rxe_elem_type } rxe_elem_type ;
struct TYPE_2__ {size_t size; int flags; int /*<<< orphan*/  key_size; int /*<<< orphan*/  key_offset; int /*<<< orphan*/  min_index; int /*<<< orphan*/  max_index; int /*<<< orphan*/  cleanup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_ROOT ; 
 int /*<<< orphan*/  RXE_POOL_ALIGN ; 
 int RXE_POOL_INDEX ; 
 int RXE_POOL_KEY ; 
 int /*<<< orphan*/  RXE_POOL_STATE_VALID ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct rxe_pool*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int rxe_pool_init_index (struct rxe_pool*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* rxe_type_info ; 

int rxe_pool_init(
	struct rxe_dev		*rxe,
	struct rxe_pool		*pool,
	enum rxe_elem_type	type,
	unsigned int		max_elem)
{
	int			err = 0;
	size_t			size = rxe_type_info[type].size;

	memset(pool, 0, sizeof(*pool));

	pool->rxe		= rxe;
	pool->type		= type;
	pool->max_elem		= max_elem;
	pool->elem_size		= ALIGN(size, RXE_POOL_ALIGN);
	pool->flags		= rxe_type_info[type].flags;
	pool->tree		= RB_ROOT;
	pool->cleanup		= rxe_type_info[type].cleanup;

	atomic_set(&pool->num_elem, 0);

	kref_init(&pool->ref_cnt);

	rwlock_init(&pool->pool_lock);

	if (rxe_type_info[type].flags & RXE_POOL_INDEX) {
		err = rxe_pool_init_index(pool,
					  rxe_type_info[type].max_index,
					  rxe_type_info[type].min_index);
		if (err)
			goto out;
	}

	if (rxe_type_info[type].flags & RXE_POOL_KEY) {
		pool->key_offset = rxe_type_info[type].key_offset;
		pool->key_size = rxe_type_info[type].key_size;
	}

	pool->state = RXE_POOL_STATE_VALID;

out:
	return err;
}