#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct hns3_nic_priv {TYPE_3__* ring_data; struct hnae3_handle* ae_handle; } ;
struct TYPE_4__ {int num_tqps; void* num_desc; } ;
struct hnae3_handle {TYPE_1__ kinfo; } ;
struct TYPE_6__ {TYPE_2__* ring; } ;
struct TYPE_5__ {void* desc_num; } ;

/* Variables and functions */
 int hns3_init_all_ring (struct hns3_nic_priv*) ; 

__attribute__((used)) static int hns3_change_all_ring_bd_num(struct hns3_nic_priv *priv,
				       u32 new_desc_num)
{
	struct hnae3_handle *h = priv->ae_handle;
	int i;

	h->kinfo.num_desc = new_desc_num;

	for (i = 0; i < h->kinfo.num_tqps * 2; i++)
		priv->ring_data[i].ring->desc_num = new_desc_num;

	return hns3_init_all_ring(priv);
}