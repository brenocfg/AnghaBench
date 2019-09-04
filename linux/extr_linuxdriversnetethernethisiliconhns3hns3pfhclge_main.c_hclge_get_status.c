#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct TYPE_3__ {int link; } ;
struct TYPE_4__ {TYPE_1__ mac; } ;
struct hclge_dev {TYPE_2__ hw; } ;

/* Variables and functions */
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 
 int /*<<< orphan*/  hclge_update_link_status (struct hclge_dev*) ; 

__attribute__((used)) static int hclge_get_status(struct hnae3_handle *handle)
{
	struct hclge_vport *vport = hclge_get_vport(handle);
	struct hclge_dev *hdev = vport->back;

	hclge_update_link_status(hdev);

	return hdev->hw.mac.link;
}