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
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int num_tqps; scalar_t__ rss_size_max; TYPE_1__* htqp; } ;
struct TYPE_2__ {int /*<<< orphan*/  alloced; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static void hclge_get_tqps_and_rss_info(struct hnae3_handle *handle,
					u16 *free_tqps, u16 *max_rss_size)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;
	u16 temp_tqps = 0;
	int i;

	for (i = 0; i < hdev->num_tqps; i++) {
		if (!hdev->htqp[i].alloced)
			temp_tqps++;
	}
	*free_tqps = temp_tqps;
	*max_rss_size = hdev->rss_size_max;
}