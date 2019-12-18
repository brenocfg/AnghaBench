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
struct hnae3_ring_chain_node {int dummy; } ;
struct hnae3_handle {TYPE_1__* pdev; } ;
struct hclgevf_dev {int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCLGEVF_STATE_RST_HANDLING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 struct hclgevf_dev* hclgevf_ae_get_hdev (struct hnae3_handle*) ; 
 int hclgevf_bind_ring_to_vector (struct hnae3_handle*,int,int,struct hnae3_ring_chain_node*) ; 
 int hclgevf_get_vector_index (struct hclgevf_dev*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclgevf_unmap_ring_from_vector(
				struct hnae3_handle *handle,
				int vector,
				struct hnae3_ring_chain_node *ring_chain)
{
	struct hclgevf_dev *hdev = hclgevf_ae_get_hdev(handle);
	int ret, vector_id;

	if (test_bit(HCLGEVF_STATE_RST_HANDLING, &hdev->state))
		return 0;

	vector_id = hclgevf_get_vector_index(hdev, vector);
	if (vector_id < 0) {
		dev_err(&handle->pdev->dev,
			"Get vector index fail. ret =%d\n", vector_id);
		return vector_id;
	}

	ret = hclgevf_bind_ring_to_vector(handle, false, vector_id, ring_chain);
	if (ret)
		dev_err(&handle->pdev->dev,
			"Unmap ring from vector fail. vector=%d, ret =%d\n",
			vector_id,
			ret);

	return ret;
}