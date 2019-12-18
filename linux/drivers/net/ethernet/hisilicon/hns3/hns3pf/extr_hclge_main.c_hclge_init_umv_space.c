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
typedef  scalar_t__ u16 ;
struct hclge_dev {scalar_t__ wanted_umv_size; int max_umv_size; int priv_umv_size; int num_req_vfs; int share_umv_size; int /*<<< orphan*/  umv_mutex; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int hclge_set_umv_space (struct hclge_dev*,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_init_umv_space(struct hclge_dev *hdev)
{
	u16 allocated_size = 0;
	int ret;

	ret = hclge_set_umv_space(hdev, hdev->wanted_umv_size, &allocated_size,
				  true);
	if (ret)
		return ret;

	if (allocated_size < hdev->wanted_umv_size)
		dev_warn(&hdev->pdev->dev,
			 "Alloc umv space failed, want %d, get %d\n",
			 hdev->wanted_umv_size, allocated_size);

	mutex_init(&hdev->umv_mutex);
	hdev->max_umv_size = allocated_size;
	/* divide max_umv_size by (hdev->num_req_vfs + 2), in order to
	 * preserve some unicast mac vlan table entries shared by pf
	 * and its vfs.
	 */
	hdev->priv_umv_size = hdev->max_umv_size / (hdev->num_req_vfs + 2);
	hdev->share_umv_size = hdev->priv_umv_size +
			hdev->max_umv_size % (hdev->num_req_vfs + 2);

	return 0;
}