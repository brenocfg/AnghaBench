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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hclge_free_vector (struct hclge_dev*,int) ; 
 int hclge_get_vector_index (struct hclge_dev*,int) ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static int hclge_put_vector(struct hnae3_handle *handle, int vector)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	int vector_id;

	vector_id = hclge_get_vector_index(hdev, vector);
	if (vector_id < 0) {
		dev_err(&hdev->pdev->dev,
			"Get vector index fail. vector_id =%d\n", vector_id);
		return vector_id;
	}

	hclge_free_vector(hdev, vector_id);

	return 0;
}