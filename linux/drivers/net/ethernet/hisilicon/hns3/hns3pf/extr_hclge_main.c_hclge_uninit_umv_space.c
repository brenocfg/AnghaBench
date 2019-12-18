#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct hclge_dev {scalar_t__ max_umv_size; int /*<<< orphan*/  umv_mutex; } ;

/* Variables and functions */
 int hclge_set_umv_space (struct hclge_dev*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hclge_uninit_umv_space(struct hclge_dev *hdev)
{
	int ret;

	if (hdev->max_umv_size > 0) {
		ret = hclge_set_umv_space(hdev, hdev->max_umv_size, NULL,
					  false);
		if (ret)
			return ret;
		hdev->max_umv_size = 0;
	}
	mutex_destroy(&hdev->umv_mutex);

	return 0;
}