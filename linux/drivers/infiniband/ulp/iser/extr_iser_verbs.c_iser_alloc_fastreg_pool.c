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
struct iser_fr_pool {scalar_t__ size; int /*<<< orphan*/  all_list; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct iser_fr_desc {int /*<<< orphan*/  all_list; int /*<<< orphan*/  list; } ;
struct iser_device {int /*<<< orphan*/  pd; } ;
struct ib_conn {int /*<<< orphan*/  pi_support; struct iser_fr_pool fr_pool; struct iser_device* device; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct iser_fr_desc*) ; 
 int PTR_ERR (struct iser_fr_desc*) ; 
 struct iser_fr_desc* iser_create_fastreg_desc (struct iser_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  iser_free_fastreg_pool (struct ib_conn*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int iser_alloc_fastreg_pool(struct ib_conn *ib_conn,
			    unsigned cmds_max,
			    unsigned int size)
{
	struct iser_device *device = ib_conn->device;
	struct iser_fr_pool *fr_pool = &ib_conn->fr_pool;
	struct iser_fr_desc *desc;
	int i, ret;

	INIT_LIST_HEAD(&fr_pool->list);
	INIT_LIST_HEAD(&fr_pool->all_list);
	spin_lock_init(&fr_pool->lock);
	fr_pool->size = 0;
	for (i = 0; i < cmds_max; i++) {
		desc = iser_create_fastreg_desc(device, device->pd,
						ib_conn->pi_support, size);
		if (IS_ERR(desc)) {
			ret = PTR_ERR(desc);
			goto err;
		}

		list_add_tail(&desc->list, &fr_pool->list);
		list_add_tail(&desc->all_list, &fr_pool->all_list);
		fr_pool->size++;
	}

	return 0;

err:
	iser_free_fastreg_pool(ib_conn);
	return ret;
}