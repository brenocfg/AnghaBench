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
struct TYPE_5__ {scalar_t__ num_vectors; int /*<<< orphan*/  roce_io_base; int /*<<< orphan*/  netdev; int /*<<< orphan*/  base_vector; } ;
struct TYPE_4__ {int /*<<< orphan*/  netdev; } ;
struct hnae3_handle {int /*<<< orphan*/  numa_node_mask; int /*<<< orphan*/  ae_algo; int /*<<< orphan*/  pdev; TYPE_2__ rinfo; TYPE_1__ kinfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  io_base; } ;
struct hclgevf_dev {scalar_t__ num_roce_msix; scalar_t__ num_msi_left; TYPE_3__ hw; int /*<<< orphan*/  roce_base_vector; struct hnae3_handle nic; struct hnae3_handle roce; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int hclgevf_init_roce_base_info(struct hclgevf_dev *hdev)
{
	struct hnae3_handle *roce = &hdev->roce;
	struct hnae3_handle *nic = &hdev->nic;

	roce->rinfo.num_vectors = hdev->num_roce_msix;

	if (hdev->num_msi_left < roce->rinfo.num_vectors ||
	    hdev->num_msi_left == 0)
		return -EINVAL;

	roce->rinfo.base_vector = hdev->roce_base_vector;

	roce->rinfo.netdev = nic->kinfo.netdev;
	roce->rinfo.roce_io_base = hdev->hw.io_base;

	roce->pdev = nic->pdev;
	roce->ae_algo = nic->ae_algo;
	roce->numa_node_mask = nic->numa_node_mask;

	return 0;
}