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
struct TYPE_6__ {scalar_t__ num_vectors; int /*<<< orphan*/  roce_io_base; int /*<<< orphan*/  netdev; int /*<<< orphan*/  base_vector; } ;
struct TYPE_5__ {int /*<<< orphan*/  netdev; } ;
struct hnae3_handle {int /*<<< orphan*/  numa_node_mask; int /*<<< orphan*/  ae_algo; int /*<<< orphan*/  pdev; TYPE_2__ rinfo; TYPE_1__ kinfo; } ;
struct hclge_vport {TYPE_4__* back; struct hnae3_handle roce; struct hnae3_handle nic; } ;
struct TYPE_7__ {int /*<<< orphan*/  io_base; } ;
struct TYPE_8__ {scalar_t__ num_roce_msi; scalar_t__ num_msi_left; TYPE_3__ hw; int /*<<< orphan*/  roce_base_vector; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hclge_init_roce_base_info(struct hclge_vport *vport)
{
	struct hnae3_handle *roce = &vport->roce;
	struct hnae3_handle *nic = &vport->nic;

	roce->rinfo.num_vectors = vport->back->num_roce_msi;

	if (vport->back->num_msi_left < vport->roce.rinfo.num_vectors ||
	    vport->back->num_msi_left == 0)
		return -EINVAL;

	roce->rinfo.base_vector = vport->back->roce_base_vector;

	roce->rinfo.netdev = nic->kinfo.netdev;
	roce->rinfo.roce_io_base = vport->back->hw.io_base;

	roce->pdev = nic->pdev;
	roce->ae_algo = nic->ae_algo;
	roce->numa_node_mask = nic->numa_node_mask;

	return 0;
}