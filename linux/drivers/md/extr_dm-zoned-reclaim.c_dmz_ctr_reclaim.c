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
struct dmz_reclaim {int /*<<< orphan*/ * kc; int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  kc_throttle; int /*<<< orphan*/  atime; struct dmz_metadata* metadata; struct dmz_dev* dev; } ;
struct dmz_metadata {int dummy; } ;
struct dmz_dev {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WQ_MEM_RECLAIM ; 
 int /*<<< orphan*/  alloc_ordered_workqueue (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dm_kcopyd_client_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dm_kcopyd_client_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmz_reclaim_work ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kfree (struct dmz_reclaim*) ; 
 struct dmz_reclaim* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dmz_ctr_reclaim(struct dmz_dev *dev, struct dmz_metadata *zmd,
		    struct dmz_reclaim **reclaim)
{
	struct dmz_reclaim *zrc;
	int ret;

	zrc = kzalloc(sizeof(struct dmz_reclaim), GFP_KERNEL);
	if (!zrc)
		return -ENOMEM;

	zrc->dev = dev;
	zrc->metadata = zmd;
	zrc->atime = jiffies;

	/* Reclaim kcopyd client */
	zrc->kc = dm_kcopyd_client_create(&zrc->kc_throttle);
	if (IS_ERR(zrc->kc)) {
		ret = PTR_ERR(zrc->kc);
		zrc->kc = NULL;
		goto err;
	}

	/* Reclaim work */
	INIT_DELAYED_WORK(&zrc->work, dmz_reclaim_work);
	zrc->wq = alloc_ordered_workqueue("dmz_rwq_%s", WQ_MEM_RECLAIM,
					  dev->name);
	if (!zrc->wq) {
		ret = -ENOMEM;
		goto err;
	}

	*reclaim = zrc;
	queue_delayed_work(zrc->wq, &zrc->work, 0);

	return 0;
err:
	if (zrc->kc)
		dm_kcopyd_client_destroy(zrc->kc);
	kfree(zrc);

	return ret;
}