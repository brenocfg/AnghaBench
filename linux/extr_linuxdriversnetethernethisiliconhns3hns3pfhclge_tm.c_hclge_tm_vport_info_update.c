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
typedef  scalar_t__ u32 ;
struct hclge_vport {int dummy; } ;
struct hclge_dev {scalar_t__ num_alloc_vport; struct hclge_vport* vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  hclge_tm_vport_tc_info_update (struct hclge_vport*) ; 

__attribute__((used)) static void hclge_tm_vport_info_update(struct hclge_dev *hdev)
{
	struct hclge_vport *vport = hdev->vport;
	u32 i;

	for (i = 0; i < hdev->num_alloc_vport; i++) {
		hclge_tm_vport_tc_info_update(vport);

		vport++;
	}
}