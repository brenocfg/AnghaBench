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
struct hns3_nic_priv {TYPE_1__* ring_data; struct hnae3_handle* ae_handle; } ;
struct TYPE_4__ {int num_tqps; } ;
struct hnae3_handle {TYPE_2__ kinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  hns3_fini_ring (int /*<<< orphan*/ ) ; 

int hns3_uninit_all_ring(struct hns3_nic_priv *priv)
{
	struct hnae3_handle *h = priv->ae_handle;
	int i;

	for (i = 0; i < h->kinfo.num_tqps; i++) {
		hns3_fini_ring(priv->ring_data[i].ring);
		hns3_fini_ring(priv->ring_data[i + h->kinfo.num_tqps].ring);
	}
	return 0;
}