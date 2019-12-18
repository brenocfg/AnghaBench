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
struct i3c_ibi_setup {unsigned int num_slots; int max_payload_len; } ;
struct TYPE_2__ {void* data; } ;
struct i3c_generic_ibi_slot {int /*<<< orphan*/  node; TYPE_1__ base; } ;
struct i3c_generic_ibi_pool {int /*<<< orphan*/  num_slots; int /*<<< orphan*/  free_slots; void* payload_buf; struct i3c_generic_ibi_slot* slots; int /*<<< orphan*/  pending; int /*<<< orphan*/  lock; } ;
struct i3c_dev_desc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct i3c_generic_ibi_pool* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3c_generic_ibi_free_pool (struct i3c_generic_ibi_pool*) ; 
 int /*<<< orphan*/  i3c_master_init_ibi_slot (struct i3c_dev_desc*,TYPE_1__*) ; 
 void* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 struct i3c_generic_ibi_pool* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct i3c_generic_ibi_pool *
i3c_generic_ibi_alloc_pool(struct i3c_dev_desc *dev,
			   const struct i3c_ibi_setup *req)
{
	struct i3c_generic_ibi_pool *pool;
	struct i3c_generic_ibi_slot *slot;
	unsigned int i;
	int ret;

	pool = kzalloc(sizeof(*pool), GFP_KERNEL);
	if (!pool)
		return ERR_PTR(-ENOMEM);

	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free_slots);
	INIT_LIST_HEAD(&pool->pending);

	pool->slots = kcalloc(req->num_slots, sizeof(*slot), GFP_KERNEL);
	if (!pool->slots) {
		ret = -ENOMEM;
		goto err_free_pool;
	}

	if (req->max_payload_len) {
		pool->payload_buf = kcalloc(req->num_slots,
					    req->max_payload_len, GFP_KERNEL);
		if (!pool->payload_buf) {
			ret = -ENOMEM;
			goto err_free_pool;
		}
	}

	for (i = 0; i < req->num_slots; i++) {
		slot = &pool->slots[i];
		i3c_master_init_ibi_slot(dev, &slot->base);

		if (req->max_payload_len)
			slot->base.data = pool->payload_buf +
					  (i * req->max_payload_len);

		list_add_tail(&slot->node, &pool->free_slots);
		pool->num_slots++;
	}

	return pool;

err_free_pool:
	i3c_generic_ibi_free_pool(pool);
	return ERR_PTR(ret);
}