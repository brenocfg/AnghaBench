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
typedef  int /*<<< orphan*/  u8 ;
struct hnae3_handle {int dummy; } ;
struct hclge_vport {struct hclge_dev* back; } ;
struct hclge_dev {int flag; int /*<<< orphan*/  dcbx_cap; } ;

/* Variables and functions */
 int HCLGE_FLAG_MQPRIO_ENABLE ; 
 struct hclge_vport* hclge_get_vport (struct hnae3_handle*) ; 

__attribute__((used)) static u8 hclge_getdcbx(struct hnae3_handle *h)
{
	struct hclge_vport *vport = hclge_get_vport(h);
	struct hclge_dev *hdev = vport->back;

	if (hdev->flag & HCLGE_FLAG_MQPRIO_ENABLE)
		return 0;

	return hdev->dcbx_cap;
}