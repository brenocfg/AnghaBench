#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hns3_nic_priv {TYPE_1__* ring_data; int /*<<< orphan*/  dev; struct hnae3_handle* ae_handle; } ;
struct TYPE_6__ {int num_tqps; } ;
struct hnae3_handle {TYPE_2__ kinfo; } ;
struct TYPE_7__ {int /*<<< orphan*/  syncp; } ;
struct TYPE_5__ {TYPE_3__* ring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int hns3_alloc_ring_memory (TYPE_3__*) ; 
 int /*<<< orphan*/  hns3_fini_ring (TYPE_3__*) ; 
 int /*<<< orphan*/  u64_stats_init (int /*<<< orphan*/ *) ; 

int hns3_init_all_ring(struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;
	int ring_num = h->kinfo.num_tqps * 2;
	int i, j;
	int ret;

	for (i = 0; i < ring_num; i++) {
		ret = hns3_alloc_ring_memory(priv->ring_data[i].ring);
		if (ret) {
			dev_err(priv->dev,
				"Alloc ring memory fail! ret=%d\n", ret);
			goto out_when_alloc_ring_memory;
		}

		u64_stats_init(&priv->ring_data[i].ring->syncp);
	}

	return 0;

out_when_alloc_ring_memory:
	for (j = i - 1; j >= 0; j--)
		hns3_fini_ring(priv->ring_data[j].ring);

	return -ENOMEM;
}