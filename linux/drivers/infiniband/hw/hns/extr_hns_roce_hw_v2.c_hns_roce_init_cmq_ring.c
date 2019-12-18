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
struct hns_roce_v2_cmq_ring {int flag; scalar_t__ next_to_use; scalar_t__ next_to_clean; } ;
struct TYPE_2__ {struct hns_roce_v2_cmq_ring crq; struct hns_roce_v2_cmq_ring csq; } ;
struct hns_roce_v2_priv {TYPE_1__ cmq; } ;
struct hns_roce_dev {scalar_t__ priv; } ;

/* Variables and functions */
 int TYPE_CSQ ; 
 int hns_roce_alloc_cmq_desc (struct hns_roce_dev*,struct hns_roce_v2_cmq_ring*) ; 

__attribute__((used)) static int hns_roce_init_cmq_ring(struct hns_roce_dev *hr_dev, bool ring_type)
{
	struct hns_roce_v2_priv *priv = (struct hns_roce_v2_priv *)hr_dev->priv;
	struct hns_roce_v2_cmq_ring *ring = (ring_type == TYPE_CSQ) ?
					    &priv->cmq.csq : &priv->cmq.crq;

	ring->flag = ring_type;
	ring->next_to_clean = 0;
	ring->next_to_use = 0;

	return hns_roce_alloc_cmq_desc(hr_dev, ring);
}