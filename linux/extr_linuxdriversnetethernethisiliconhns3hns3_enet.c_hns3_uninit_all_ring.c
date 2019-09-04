#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hns3_nic_priv {TYPE_2__* ring_data; struct hnae3_handle* ae_handle; } ;
struct TYPE_7__ {int num_tqps; } ;
struct hnae3_handle {TYPE_3__ kinfo; TYPE_1__* ae_algo; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* reset_queue ) (struct hnae3_handle*,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  ring; } ;
struct TYPE_5__ {TYPE_4__* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_fini_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hnae3_handle*,int) ; 

int hns3_uninit_all_ring(struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;
	int i;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		if (h->ae_algo->ops->reset_queue)
			h->ae_algo->ops->reset_queue(h, i);

		hns3_fini_ring(priv->ring_data[i].ring);
		hns3_fini_ring(priv->ring_data[i + h->kinfo.num_tqps].ring);
	}
	return 0;
}