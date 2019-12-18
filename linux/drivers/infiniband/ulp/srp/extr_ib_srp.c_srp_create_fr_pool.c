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
struct srp_fr_pool {int size; int max_page_list_len; int /*<<< orphan*/  free_list; struct srp_fr_desc* desc; int /*<<< orphan*/  lock; } ;
struct srp_fr_desc {int /*<<< orphan*/  entry; struct ib_mr* mr; } ;
struct ib_pd {int dummy; } ;
struct ib_mr {int dummy; } ;
struct TYPE_2__ {int device_cap_flags; } ;
struct ib_device {int /*<<< orphan*/  dev; TYPE_1__ attrs; } ;
typedef  enum ib_mr_type { ____Placeholder_ib_mr_type } ib_mr_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 struct srp_fr_pool* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IB_DEVICE_SG_GAPS_REG ; 
 int IB_MR_TYPE_MEM_REG ; 
 int IB_MR_TYPE_SG_GAPS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct ib_mr*) ; 
 int PTR_ERR (struct ib_mr*) ; 
 int /*<<< orphan*/  desc ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 struct ib_mr* ib_alloc_mr (struct ib_pd*,int,int) ; 
 struct srp_fr_pool* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srp_destroy_fr_pool (struct srp_fr_pool*) ; 
 int /*<<< orphan*/  struct_size (struct srp_fr_pool*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct srp_fr_pool *srp_create_fr_pool(struct ib_device *device,
					      struct ib_pd *pd, int pool_size,
					      int max_page_list_len)
{
	struct srp_fr_pool *pool;
	struct srp_fr_desc *d;
	struct ib_mr *mr;
	int i, ret = -EINVAL;
	enum ib_mr_type mr_type;

	if (pool_size <= 0)
		goto err;
	ret = -ENOMEM;
	pool = kzalloc(struct_size(pool, desc, pool_size), GFP_KERNEL);
	if (!pool)
		goto err;
	pool->size = pool_size;
	pool->max_page_list_len = max_page_list_len;
	spin_lock_init(&pool->lock);
	INIT_LIST_HEAD(&pool->free_list);

	if (device->attrs.device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		mr_type = IB_MR_TYPE_SG_GAPS;
	else
		mr_type = IB_MR_TYPE_MEM_REG;

	for (i = 0, d = &pool->desc[0]; i < pool->size; i++, d++) {
		mr = ib_alloc_mr(pd, mr_type, max_page_list_len);
		if (IS_ERR(mr)) {
			ret = PTR_ERR(mr);
			if (ret == -ENOMEM)
				pr_info("%s: ib_alloc_mr() failed. Try to reduce max_cmd_per_lun, max_sect or ch_count\n",
					dev_name(&device->dev));
			goto destroy_pool;
		}
		d->mr = mr;
		list_add_tail(&d->entry, &pool->free_list);
	}

out:
	return pool;

destroy_pool:
	srp_destroy_fr_pool(pool);

err:
	pool = ERR_PTR(ret);
	goto out;
}