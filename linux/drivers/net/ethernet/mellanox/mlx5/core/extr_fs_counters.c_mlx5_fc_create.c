#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fc_stats {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  addlist; int /*<<< orphan*/  counters_idr_lock; int /*<<< orphan*/  counters_idr; } ;
struct TYPE_4__ {int /*<<< orphan*/  packets; int /*<<< orphan*/  bytes; int /*<<< orphan*/  lastuse; } ;
struct mlx5_fc {int aging; int /*<<< orphan*/  addlist; TYPE_2__ cache; int /*<<< orphan*/  lastpackets; int /*<<< orphan*/  lastbytes; int /*<<< orphan*/  id; int /*<<< orphan*/  list; } ;
struct TYPE_3__ {struct mlx5_fc_stats fc_stats; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 struct mlx5_fc* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct mlx5_fc*) ; 
 int idr_alloc_u32 (int /*<<< orphan*/ *,struct mlx5_fc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_preload_end () ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  llist_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_fc* mlx5_fc_acquire (struct mlx5_core_dev*,int) ; 
 int /*<<< orphan*/  mlx5_fc_release (struct mlx5_core_dev*,struct mlx5_fc*) ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_fc *mlx5_fc_create(struct mlx5_core_dev *dev, bool aging)
{
	struct mlx5_fc *counter = mlx5_fc_acquire(dev, aging);
	struct mlx5_fc_stats *fc_stats = &dev->priv.fc_stats;
	int err;

	if (IS_ERR(counter))
		return counter;

	INIT_LIST_HEAD(&counter->list);
	counter->aging = aging;

	if (aging) {
		u32 id = counter->id;

		counter->cache.lastuse = jiffies;
		counter->lastbytes = counter->cache.bytes;
		counter->lastpackets = counter->cache.packets;

		idr_preload(GFP_KERNEL);
		spin_lock(&fc_stats->counters_idr_lock);

		err = idr_alloc_u32(&fc_stats->counters_idr, counter, &id, id,
				    GFP_NOWAIT);

		spin_unlock(&fc_stats->counters_idr_lock);
		idr_preload_end();
		if (err)
			goto err_out_alloc;

		llist_add(&counter->addlist, &fc_stats->addlist);

		mod_delayed_work(fc_stats->wq, &fc_stats->work, 0);
	}

	return counter;

err_out_alloc:
	mlx5_fc_release(dev, counter);
	return ERR_PTR(err);
}